/*
 * ============================================================================
 *
 *       Filename:  garp.c
 *
 *    Description:  Simple implementation of a gratuitous ARP packet.
 *
 *        Created:  02/03/2017 09:30:35 PM
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Computer Science Community
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include <linux/if_ether.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#include "garp.h"
#include "garp_config.h"

void
usage ()
{
    fprintf(stdout,
        "Gratuitous ARP %d.%d\n\n"
        "Usage: garp iface addr\n"
        "Example: garp eth0 192.168.1.42\n",
        GARP_VERSION_MAJOR, GARP_VERSION_MINOR
    );
}

void
set_iface (char iface[25], char *argv_iface)
{
    strncpy(iface, argv_iface, strlen(argv_iface));
}

void
set_ip (struct in_addr* source_addr, char* argv_addr)
{
    source_addr->s_addr = inet_addr(argv_addr);
}

void
get_mac_address (unsigned char source_eth_addr[ETHERNET_ADDR_LEN], char* iface,
				 int *sll_ifindex)
{
    struct ifreq ethernet;
    strncpy(ethernet.ifr_name, iface, IF_NAMESIZE);
    int file_descriptor = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    if(ioctl(file_descriptor, SIOCGIFHWADDR, &ethernet) == -1) {
        fprintf(stderr, "Error: Cannot get ethernet address\n");
        fprintf(stderr, strerror(errno));
        exit(1);
    } else {
        sprintf(
            source_eth_addr, "%s",
            (unsigned char *) ethernet.ifr_hwaddr.sa_data
        );
		*sll_ifindex = ethernet.ifr_ifindex;
    }
    close(file_descriptor);
}

void
print_raw_packet (struct gratuitous_arp *packet, unsigned int packet_len)
{
    char buffer[packet_len];

    memcpy(buffer, packet, packet_len);

    for(int i = 0; i < packet_len; i++) {
        fprintf(stdout, "%.2X ", buffer[i] & 0xff);
    }
    fprintf(stdout, "\n");
}

void
send_gratuitous_arp (int socket_fd, struct gratuitous_arp* arp,
                     struct sockaddr_ll* addr)
{
    int ok = sendto(socket_fd, arp, sizeof(*arp), 0, (struct sockaddr *)addr, sizeof(*addr));

    if(!ok) {
        fprintf(stderr, "Error on sending packet");
        fprintf(stderr, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int
main (int argc, char* argv[])
{
    if(argc != 3) {
        fprintf(stderr, "Error: Wrong number of arguments %d\n\n", argc);
        usage();
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Sending gratuitous ARP..\n");

    /* Interface name used to send packet */
    char iface[25];

    /* Structs to store source and target addresses */
    struct in_addr source_ip_address;

    /* The Gratuitous ARP packet data */
    struct gratuitous_arp packet;

    /* The link layer packet */
    struct sockaddr_ll link_address;

    /* File descriptor of the socket local socket */
    int socket_fd;

    /* Sets interface name from program arguments */
    set_iface(iface, argv[1]);

    /* Sets the IP address that we will fake */
    set_ip(&source_ip_address, argv[2]);

    /* Tries to create a socket */
    socket_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if(socket_fd < 0) {
        fprintf(stderr, "Error on creating socket");
        return EXIT_FAILURE;
    }


    link_address.sll_family = AF_PACKET;
	link_address.sll_protocol = htons(ETH_P_ARP);

    /* Fill data for Ethernet header */
    get_mac_address(packet.source_ethernet_address, iface, &link_address.sll_ifindex);
    memset(packet.target_ethernet_address, 0xFF, ETHERNET_ADDR_LEN);
    packet.ethernet_type = htons(ETHERNET_TYPE);

    /* Copy data into ARP packet buffer */
    packet.hardware_type = htons(ETHERNET_ARP_TYPE);
    packet.protocol_type = htons(IP_TYPE);
    packet.hardware_address_length = ETHERNET_ADDR_LEN;
    packet.protocol_address_length = IP_ADDR_LEN;
    packet.arp_options = htons(REQUEST_OPERATION);

    /* Gets the local interface hardware (Ethernet) address */
    memcpy(packet.source_hardware_address, packet.source_ethernet_address, ETHERNET_ADDR_LEN);
    memcpy(packet.source_protocol_address, &source_ip_address, IP_ADDR_LEN);

    memcpy(packet.target_hardware_address, packet.target_ethernet_address, ETHERNET_ADDR_LEN);
    memcpy(packet.target_protocol_address, &source_ip_address, IP_ADDR_LEN);

    /* Just adding extra padding data */
    memset(packet.padding, 0, ARP_PADDING_SIZE);

    /* Sends the packet out */
    send_gratuitous_arp(socket_fd, &packet, &link_address);

    /* Debug hex decimal data */
    print_raw_packet(&packet, sizeof(packet));

    /* Closes the socket */
    close(socket_fd);

    return EXIT_SUCCESS;
}
