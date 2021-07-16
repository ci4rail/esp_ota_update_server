# ESP OTA Update Server Examples

In this folder the examples for the usage of the ota update server can be found.

## Folder Structure

```
examples
├── device
│   ├── cdc_ecm_ota       # update server example with the cdc-ecm interface
|   |   ├── main          # source code
|   |   └── server_certs  # server certificate folder
│   └── ethernet_ota      # update server example with the ethernet interface
|       ├── main          # source code
|       └── server_certs  # server certificate folder
└── host
    └── https_server      # https server running on the host
```

## Usage

Copy the example of your choice next to the folder of the ota update server component:
```
$ cp -r ./esp_ota_update_server/examples/device/<example-folder> .
```
Build it with the esp-idf framework and flash the binary onto your ESP32(S2) board. Connect the microcontroller via USB with the host computer. For the IP-Address assignment check the README of the corresponding example.
After the IP-Address(es) have been set, copy the new firmware binary to the https_server folder and adapt the https_server.py file. Insert the binary name in the URL string variable.
Run the https server:
```
python https_server.py
```
If you monitor the output of the ESP32(S2) you will now see that one of the ota partitions is being written to and the ESP32(S2) is restarted.
