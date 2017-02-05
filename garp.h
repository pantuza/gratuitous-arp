
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



/**
 * Only variable values for this program. As we always send a ARP reply, other
 * protocol fields does not change.
 */
struct gratuitous_arp {

    char source_eth_addr[ETHERNET_ADDR_LEN];  /* Source Ethernet address */
    char source_ip_addr[IP_ADDR_LEN];  /* Source IP address */

    char target_eth_addr[ETHERNET_ADDR_LEN];  /* Target Ethernet address */
    char target_ip_addr[IP_ADDR_LEN];  /* Target IP address */
};



#endif /* GARP_H */
