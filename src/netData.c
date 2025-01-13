#include "headers/netData.h"

char* setHostAddress() {

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

void get_all_interfaces(WINDOW *win) {    
    struct ifaddrs *inter, *ifa;
    int family;
    char addrv4[INET_ADDRSTRLEN];
    char netmask[INET_ADDRSTRLEN];
    char addrv6[INET6_ADDRSTRLEN];
    struct in6_addr *netmask6;

    //gets the list of all interfaces
    if(getifaddrs(&inter) == -1) {
        endwin();
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
            printw("Interface...: %s\n", ifa->ifa_name);
            printw("IPv4_Address: %s\n",addrv4);
            printw("Subnet_mask.: %s\n\n", netmask);
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
            printw("Interface...: %s\n", ifa->ifa_name);
            printw("IPv6_Address: %s\n", addrv6);
            printw("Prefixlen...: %d\n\n", prefix_len);
        }
    }

    refresh();

    freeifaddrs(inter);    
}

void netData_menu() {
    int loopCheck=TRUE;

    initscr();
    attron(A_BOLD);;
    printw("#    #   ######   #######      #       #   ######   #    #   #    #\n");
    printw("##   #   #           #         ##     ##   #        ##   #   #    #\n");
    printw("# #  #   ######      #         # #   # #   ######   # #  #   #    #\n");
    printw("#  # #   #           #         #  # #  #   #        #  # #   #    #\n");
    printw("#   ##   ######      #         #   #   #   ######   #   ##    ####\n\n\n");
    attroff(A_BOLD);
    while(loopCheck != FALSE) {
        int menu_option = 0;
        attron(A_BOLD);
        printw("For your HTTP server please select a menu option:\n");
        printw("1. Print host interface data    2. Set host Ip address\n");
        attroff(A_BOLD);
        refresh();
        scanw("%d", &menu_option);
        refresh();
        switch (menu_option) {
            case INTERFACE_DATA:
                wclear(stdscr);
                wrefresh(stdscr);
                get_all_interfaces(stdscr);
                getch();
                sleep(0.50);
                break;
            case SET_HOST_IP:
                wclear(stdscr);
                wrefresh(stdscr);
                setHostAddress();
                getch();
                sleep(0.25);
                break;
            case 3:

            case EXIT_MENU:
                loopCheck = FALSE;
            default:
                break;
        }
        wclear(stdscr);
        wrefresh(stdscr);
    }
    endwin();
}

int main() {
    netData_menu();
    return 0;
}