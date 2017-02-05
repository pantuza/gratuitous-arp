
#ifndef GARP_H
#define GARP_H



/* Our implementation uses Ethernet as the ARP hardware type */
#define ETHERNET_TYPE 0x0806

/* When ARP hardware type is Ethernet its address needs 6 bytes of storage */
#define ETHERNET_ADDR_LEN 6

/* Our implementation uses IP as the ARP protocol type */
#define IP_TYPE 0x0800

/* When ARP protocol type is IP its address needs 4 bytes of storage */
#define IP_ADDR_LEN 4

/* ARP option to express reply */
#define REPLY_OPERATION 2



#endif /* GARP_H */
