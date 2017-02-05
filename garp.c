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

#include <netdb.h>
#include <sys/socket.h>

#include <linux/if_ether.h>

#include "garp.h"
#include "garp_config.h"

void
usage ()
{
    fprintf(stdout,
        "Gratuitous ARP %d.%d\n\n"
        "Usage: garp iface addr\n"
        "Example: garp eth0 192.168.1.42\n",
        garp_VERSION_MAJOR, garp_VERSION_MINOR
    );
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

    /* Structs to store source and target addresses */
    struct in_addr source_addr;
    struct in_addr target_addr;

    /* The Gratuitous ARP packet data */
    struct gratuitous_arp packet;

    /* The socket used to send packet on network */
    struct sockaddr socket_address;

    /* File descriptor of the socket local socket */
    int socket_fd;

    /* Tries to create a socket */
    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_RARP));
    if(socket_fd < 0) {
        fprintf(stderr, "Error on creating socket");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
