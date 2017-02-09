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
get_mac_address (unsigned char source_eth_addr[ETHERNET_ADDR_LEN], char* iface)
{
    struct ifreq ethernet;
    strncpy(ethernet.ifr_name, iface, strlen(iface));
    int file_descriptor = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    if(ioctl(file_descriptor, SIOCGIFHWADDR, &ethernet) == -1) {
        fprintf(stderr, "Error: Cannot get ethernet address\n");
        fprintf(stderr, strerror(errno));
        exit(1);
    } else {
        source_eth_addr = (unsigned char *) ethernet.ifr_hwaddr.sa_data;
    }
    close(file_descriptor);
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

    /* The socket used to send packet on network */
    struct sockaddr socket_address;

    /* File descriptor of the socket local socket */
    int socket_fd;

    /* Sets interface name from program arguments */
    set_iface(iface, argv[1]);

    /* Sets the interface in which packet will leave */
    strncpy(socket_address.sa_data, iface, strlen(iface));

    /* Sets the IP address that we will fake */
    set_ip(&source_ip_address, argv[2]);

    /* Tries to create a socket */
    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_RARP));
    if(socket_fd < 0) {
        fprintf(stderr, "Error on creating socket");
        return EXIT_FAILURE;
    }

    /* Closes the socket */
    close(socket_fd);

    return EXIT_SUCCESS;
}
