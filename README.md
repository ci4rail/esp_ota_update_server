# ESP-IDF OTA Update Server Component

## Description

This component provides a tcp server which awaits a message on port 1234 with a URL from which the ESP32S2 shall download a new firmware binary and write it to one of its ota partitions.

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
