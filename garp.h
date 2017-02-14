
#ifndef GARP_H
#define GARP_H


/* Ethernet type for Link layer header */
#define ETHERNET_TYPE 0x806

/* Our implementation uses Ethernet as the ARP hardware type */
#define ETHERNET_ARP_TYPE 0x0001

/* When ARP hardware type is Ethernet its address needs 6 bytes of storage */
#define ETHERNET_ADDR_LEN 6

/* Our implementation uses IP as the ARP protocol type */
#define IP_TYPE 0x0800

/* When ARP protocol type is IP its address needs 4 bytes of storage */
#define IP_ADDR_LEN 4

/* ARP option to express reply */
#define REQUEST_OPERATION 1

/* Size for the padding data */
#define ARP_PADDING_SIZE 18

/**
 * Only variable values for this program. As we always send a ARP reply, other
 * protocol fields does not change.
 */
struct gratuitous_arp {

    /* Ethernet header */
    unsigned char source_ethernet_address[ETHERNET_ADDR_LEN];
    unsigned char target_ethernet_address[ETHERNET_ADDR_LEN];
    unsigned short ethernet_type;

    /* ARP Header */
    unsigned short hardware_type;
    unsigned short protocol_type;

    unsigned char hardware_address_length;
    unsigned char protocol_address_length;

    unsigned short arp_options;

    unsigned char source_hardware_address[ETHERNET_ADDR_LEN];
    unsigned char source_protocol_address[IP_ADDR_LEN];

    unsigned char target_hardware_address[ETHERNET_ADDR_LEN];
    unsigned char target_protocol_address[IP_ADDR_LEN];

    /* Extra padding data */
    unsigned char padding[ARP_PADDING_SIZE];
};



#endif /* GARP_H */
