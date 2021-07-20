# ESP-IDF OTA Update Server Component

## Description

This component provides a tcp server which awaits a message on port 1234 with a URL from which the ESP32S2 shall download a new firmware binary and write it to one of its ota partitions. The port to listen on can be adapted via the setting CONFIG_OTA_SERVER_PORT in the configuration menu.

## EEPROM Read

In the configuration, the EEPROM Read feature can be enabled and disabled. If the feature is enabled, the tcp server sends the content of a external EEPROM to the connected client directly after the connection was accepted and before the client shall send the URL. The EEPROM is connected via I2C with the ESP32(S2). The I2C connection can be configured in the configuration menu.

## Task Watchdog
The ota update server is monitored by a task watchdog, which has to be triggered within a certain time. The allowed time window can be adjusted via the setting CONFIG_ESP_TASK_WDT_TIMEOUT_S in the configuration menu. If the ota update server is in standby and waits for a connecting client, it triggers the watchdog every 3 seconds.

ATTENTION: During the update the watchdog is not triggered. How long this may take depends on the size of the image. This time must be considered when configuring the watchdog timeout.

## Usage

An application which integrates the ota update server have to fulfill the following requirements:
 * Implement the callback function diagnostic_cb()
 * Provide the certificate for the https server
 * Provide the header ota_server_cert.h and insert the correct name of the certificate file
 * Provide the path to the certificate in the CMakefileLists file (OTA_CERT_PATH)
 * Provide the path to the ota_server_cert.h in the CMakefileLists file (OTA_SERVER_CERT_H)

For more information see example folder.

### Diagnostic Callback

If the firmware has been updated with the ota update server, the new firmware must provide the diagnostic_cb() function, which should perform some diagnostic processes on the first run and decide if everything is ok and the application should start up. If that is the case, the callback should return true. If a problem is detected, the callback should return false to indicate that a rollback should be performed.
