/*
Copyright © 2021 Ci4Rail GmbH
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#if CONFIG_READ_EEPROM

#include "driver/i2c.h"
#include "esp_log.h"
#include "lwip/sockets.h"

#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */

static const char *TAG = "send_eeprom";

static gpio_num_t i2c_gpio_sda = CONFIG_GPIO_SDA;
static gpio_num_t i2c_gpio_scl = CONFIG_GPIO_SCL;
static uint32_t i2c_frequency = CONFIG_I2C_FREQ;
static i2c_port_t i2c_port = I2C_NUM_1;
static uint8_t *eeprom_data;
static int eeprom_len = CONFIG_EEPROM_LENGTH;

static esp_err_t i2c_master_driver_initialize(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = i2c_gpio_sda,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = i2c_gpio_scl,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = i2c_frequency,
    };
    return i2c_param_config(i2c_port, &conf);
}

static esp_err_t i2c_read_eeprom(void)
{
    int chip_addr = 0x50;
    int data_addr = 0x00;

    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_master_driver_initialize();
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    if (data_addr != -1) {
        i2c_master_write_byte(cmd, chip_addr << 1 | WRITE_BIT, ACK_CHECK_EN);
        i2c_master_write_byte(cmd, data_addr, ACK_CHECK_EN);
        i2c_master_start(cmd);
    }
    i2c_master_write_byte(cmd, chip_addr << 1 | READ_BIT, ACK_CHECK_EN);
    if (eeprom_len > 1) {
        i2c_master_read(cmd, eeprom_data, eeprom_len - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, eeprom_data + eeprom_len - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
    if ( ret == ESP_OK )
    {
        ESP_LOGI(TAG, "Read EEPROM successful");
        char eeprom_content[CONFIG_EEPROM_LENGTH * 3 + 1];
        for (int i = 0; i < eeprom_len; i++) {
            snprintf(&(eeprom_content[i*3]), 4, "%02x ", eeprom_data[i]);
        }
        ESP_LOGD(TAG, "EEPROM Content: %s", eeprom_content);
    }
    else if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGW(TAG, "I2C bus is busy");
    } else {
        ESP_LOGW(TAG, "I2C read failed");
    }
    i2c_cmd_link_delete(cmd);
    i2c_driver_delete(i2c_port);
    return ret;
}

void send_eeprom(const int sock)
{
    eeprom_data = malloc(eeprom_len);
    if(eeprom_data == NULL) {
        ESP_LOGW(TAG, "Could not allocate memory!");
        return;
    }

    if(i2c_read_eeprom() == ESP_OK) {
        int written = send(sock, eeprom_data, eeprom_len, 0);
        if (written < 0) {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        }
    }
    
    free(eeprom_data);
}

#endif //CONFIG_READ_EEPROM
