cmake_minimum_required(VERSION 3.5)

set(include_public
    "${COMPONENT_DIR}/include"
    "${PROJECT_DIR}${OTA_SERVER_CERT_H}"
    )

set(include_private
    "${COMPONENT_DIR}/include_private"
    )

set(srcs
    "${COMPONENT_DIR}/src/ota_server.c"
    "${COMPONENT_DIR}/src/ota_update.c"
    "${COMPONENT_DIR}/src/send_eeprom.c"
    )

message( STATUS "${OTA_CERT_PATH}" )
message( STATUS "${PROJECT_DIR}" )

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_public}"
                       PRIV_INCLUDE_DIRS "${include_private}"
                       REQUIRES lwip tinyusb nvs_flash esp_https_ota app_update
                       EMBED_TXTFILES ${PROJECT_DIR}${OTA_CERT_PATH})
