//
// Created by admin on 9/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    struct addrinfo hints, * res, *p;

    char ipstr[INET6_ADDRSTRLEN];
    int status;
    char const* hostname = "google.com";
    char const* service = "http";

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC; // allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP only.

    if ((status = getaddrinfo(hostname, service, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    printf("IP addreses for %s:\n\n", hostname);

    for (p = res; p != NULL; p = p->ai_next) {
        void* addr;
        char const* ipver;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 =  (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s %s \n", ipver, ipstr);
    }
    freeaddrinfo(res);

    return 0;

}
