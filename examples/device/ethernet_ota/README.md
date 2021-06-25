# Ethernet OTA Example

This example shows how to use the ota update server component with the Ethernet interface.

## Usage

See examples/README.md

## Set IP-Address of Network Interface on the Host

Connect the ethernet interface of the ESP32 with the host PC and set the IP-Address of the corresponding NIC:
```
$ sudo ip addr add 192.168.7.10/24 broadcast 192.168.7.255 dev <Interface-Name>
$ sudo ip link set dev <Interface-Name> up
```

## Set IP-Address with DHCP

The ESP32s network interface acquire its IP-Address from a DHCP server running on the host. Before a firmware update can be performed, the IP-Address has to be assigned. Therefor the ISC-DHCPD can be used. It can be installed on the host PC with:
```
sudo apt install isc-dhcp-server 
```
Afterwards the DHCP server should be configured by adding the following lines to /etc/dhcp/dhcpd.conf:
```
subnet 192.168.7.0 netmask 255.255.255.0 {
  range 192.168.7.1 192.168.7.9;
}
```
With `sudo systemctl restart isc-dhcp-server` the DHCP server can be restarted and the new configuration can be applied.
If the output of the ESP32 is monitored, the following lines are displayed:
```
I (4544) ota-server: Ethernet Link Up
I (4544) ota-server: Ethernet HW Addr 98:f4:ab:21:3f:f7
I (5494) esp_netif_handlers: eth ip: 192.168.7.1, mask: 255.255.255.0, gw: 192.168.7.1
I (5494) ota-server: Ethernet Got IP Address
I (5494) ota-server: ~~~~~~~~~~~
I (5494) ota-server: ETHIP:192.168.7.1
I (5504) ota-server: ETHMASK:255.255.255.0
I (5504) ota-server: ETHGW:192.168.7.1
I (5514) ota-server: ~~~~~~~~~~~
```
If another IP-Address is assigned, the IP-Address in https_server.py has to be adapted.

## Settings for OLIMEX board ESP32-PoE-ISO

To run example on OLIMEX board ESP32-PoE-ISO the following settings has be set in menuconfig:
```
CONFIG_ETH_USE_ESP32_EMAC=y
CONFIG_ETH_PHY_INTERFACE_RMII=y
CONFIG_ETH_RMII_CLK_OUTPUT=y
CONFIG_ETH_RMII_CLK_OUT_GPIO=17
CONFIG_ETH_DMA_BUFFER_SIZE=512
CONFIG_ETH_DMA_RX_BUFFER_NUM=10
CONFIG_ETH_DMA_TX_BUFFER_NUM=10
CONFIG_ETH_USE_SPI_ETHERNET=y
CONFIG_ETH_SPI_ETHERNET_DM9051=y
CONFIG_CONTROL_PHY_POWER=y
CONFIG_PIN_PHY_POWER=12
CONFIG_EXAMPLE_USE_INTERNAL_ETHERNET=y
CONFIG_EXAMPLE_ETH_PHY_LAN8720=y
CONFIG_EXAMPLE_ETH_MDC_GPIO=23
CONFIG_EXAMPLE_ETH_MDIO_GPIO=18
CONFIG_EXAMPLE_ETH_PHY_RST_GPIO=-1
CONFIG_EXAMPLE_ETH_PHY_ADDR=0
```
