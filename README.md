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

### Contributing

Just fork, modify and send a pull request.
