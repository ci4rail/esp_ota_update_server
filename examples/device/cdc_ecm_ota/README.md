# CDC-ECM OTA Example

This example shows how to use the ota update server component with the CDC-ECM interface.

# Usage

See examples/README.md

## Set IP-Address of Network Interface on the Host

On the host computer the microcontroller is reconized as a network interface (enx<em>MAC-Address</em>). Give it the ip address 192.168.7.10 and set it up:
```
$ sudo ip addr add 192.168.7.10/24 broadcast 192.168.7.255 dev enx<MAC-Address>
$ sudo ip link set dev enx<MAC-Address> up
```
