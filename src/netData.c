#include "headers/netData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

char* selectInterface() {
    printf("\nSelect an interface Ip address to bind for the server:\n");
}

int countPrefixLen(struct in6_addr *netmask) {
    int prefix_len = 0;

    for(int i=0; i<16; i++) {
        unsigned char byte = netmask->s6_addr[i];

        for(int bit=7; bit >= 0; bit--) {
            if(byte & (1 << bit)) {
                prefix_len++;
            }
            else {
                return prefix_len;
            }
        }
    }
    return prefix_len;
}


char* get_interface() {    
    struct ifaddrs *inter, *ifa;
    int family;
    char addrv4[INET_ADDRSTRLEN];
    char netmask[INET_ADDRSTRLEN];
    char addrv6[INET6_ADDRSTRLEN];
    struct in6_addr *netmask6;

    //gets the list of all interfaces
    if(getifaddrs(&inter) == -1) {
        perror("getifaddrs"); 
        exit(1);
    }

    for (ifa = inter; ifa != NULL; ifa = ifa->ifa_next) {
        family = ifa->ifa_addr->sa_family;

        //checks for ipv4 interface
        if (family == AF_INET) {
            void *tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            inet_ntop(family, tmpAddrPtr, addrv4, sizeof(addrv4));
            
            if(ifa->ifa_netmask != NULL) {
                void *tmpNetmaskPtr = &((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr;
                inet_ntop(family, tmpNetmaskPtr, netmask, sizeof(addrv4));
            }
            else {
                snprintf(netmask, sizeof(netmask), "Unknown");
            }
            //prints interface data
            printf("Interface...: %s\n", ifa->ifa_name);
            printf("IPv4_Address: %s\n",addrv4);
            printf("Subnet_mask.: %s\n\n", netmask);
        }

        //checks for ipv6 interface
        else if(family == AF_INET6) {
            void *tmpAddrPtr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            inet_ntop(family, tmpAddrPtr, addrv6, sizeof(addrv6));
            
            int prefix_len = 0;
            if(ifa->ifa_netmask != NULL) {
                netmask6 = &((struct sockaddr_in6 *)ifa->ifa_netmask)->sin6_addr;
                prefix_len = countPrefixLen(netmask6);
            }
            //prints interface data
            printf("Interface...: %s\n", ifa->ifa_name);
            printf("IPv6_Address: %s\n", addrv6);
            printf("Prefixlen...: %d\n\n", prefix_len);
        }
    }

    freeifaddrs(inter);

    return selectInterface();    
}

int main() {
    get_interface();
    return 0;
}