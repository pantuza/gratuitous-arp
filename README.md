# Gratuitous ARP

[Gratuitous ARP](https://wiki.wireshark.org/Gratuitous_ARP) implementation written in C to mess local networks.

### Usage
```bash
$> garp eth0 192.168.1.42
```

This will send a Gratuitous ARP on eth0 interface saying that your IP address is 192.168.1.42.
As a broadcast packet, it will say to other machines in the local area network that you is responsible for answering for that IP.

### Compilation
We use [cmake](https://cmake.org/) to compile project.
Refer to project root directory and execute:

```bash
$> mkdir build
$> cd build
$> cmake ..
$> make
```
This will generate the binary file **garp**

### Address Resolution Protocol - ARP
ARP protocol maps layer 3 addresses to layer 2 addresses. A layer 3 address could be IP (IPv4) and a layer 2 address could be Ethernet (MAC address).
ARP enables a host to know which other host (MAC address) respondes to a given IP on a local area network. Also the inverse operation.
As a request and response protocol, the following image shows its base workflow:

![Basic ARP protocol workflow - Gratuitous ARP project](https://raw.githubusercontent.com/pantuza/gratuitous-arp/master/base-arp.png)

As could be seen, left host sends a **ARP request** asking for which is the MAC address (host) that responds to IPv4 10.0.0.5.
Then, right host gives the **ARP response** answering the question. Each host updates its own ARP Table.


### Contributing

Just fork, modify and send a pull request.
