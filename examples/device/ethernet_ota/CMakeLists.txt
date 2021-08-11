# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXCLUDE_COMPONENTS asio coap)
set(EXTRA_COMPONENT_DIRS ../esp_ota_update_server)

# Define where the certificate can be found (relatively to the project directory)
set(OTA_CERT_PATH /server_certs/ca_cert.pem)
# Define where ota_server_cert.h can be found (relatively to the project directory)
set(OTA_SERVER_CERT_H /server_certs)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ethernet_ota_example)
