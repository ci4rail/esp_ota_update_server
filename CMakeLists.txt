cmake_minimum_required(VERSION 3.5)

set(srcs
    "src/ota_server.c")

set(include_dirs
    "include"
    "${PROJECT_DIR}${OTA_SERVER_CERT_H}")

set(srcs
    "${COMPONENT_DIR}/src/ota_server.c")

message( STATUS "${OTA_CERT_PATH}" )
message( STATUS "${PROJECT_DIR}" )

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES lwip tinyusb nvs_flash esp_https_ota app_update
                       EMBED_TXTFILES ${PROJECT_DIR}${OTA_CERT_PATH})
