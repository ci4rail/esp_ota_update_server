# CDC-ECM OTA Example

This example shows how to use the ota update server component with the CDC-ECM interface.

## Usage

See examples/README.md

## Set IP-Address of Network Interface on the Host

On the host computer the microcontroller is reconized as a network interface (enx<em>MAC-Address</em>). Give it the ip address 192.168.7.10 and set it up:
```
$ sudo ip addr add 192.168.7.10/24 broadcast 192.168.7.255 dev enx<MAC-Address>
$ sudo ip link set dev enx<MAC-Address> up
```

## Acquire IP-Address with DHCP

The ESP32S2s internal network interface acquire its IP-Address from a DHCP server running on the host. Before a firmware update can be performed, the IP-Address has to be assigned. Therefor the ISC-DHCPD can be used. It can be installed on the host PC with:
```
sudo apt install isc-dhcp-server 
```
Then specify the interfaces to listen on in /etc/default/isc-dhcp-server:
```
INTERFACESv4="enx<MAC-Address>"
```
Afterwards the DHCP server should be configured by adding the following lines to /etc/dhcp/dhcpd.conf:
```
subnet 192.168.7.0 netmask 255.255.255.0 {
  range 192.168.7.1 192.168.7.1;
}
```
With `sudo systemctl restart isc-dhcp-server` the DHCP server can be restarted and the new configuration can be applied.
If the output of the ESP32S2 is monitored, the following lines are displayed:
```
I (9907) CDC-ECM Driver: Netif Status Changed...
I (9907) CDC-ECM Driver: IP-Address: 192.168.7.1
I (9907) CDC-ECM Driver: Netmask: 255.255.255.0
I (9912) CDC-ECM Driver: Gateway: 192.168.7.1
I (9917) CDC-ECM Driver: Link up.
```
