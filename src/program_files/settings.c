#include "../headers/settings.h"
/*
char* getAutoAddr() {

}

char* setHostAddress(WINDOW *win) {
    int bind_choice = 0;
    char* chosen_address = malloc(INET_ADDRSTRLEN);
    while(TRUE) {
        wclear(win);
        wrefresh(win);
        attron(A_BOLD);
        printw("Would you like to bind the address automatically or manually?\n");
        printw("1. Automatically    2. Manually    3. Exit\n");
        attroff(A_BOLD);
        scanw("%d", &bind_choice);
        refresh();
        switch (bind_choice) {
            case 1: 
                chosen_address = getAutoAddr();
            case 2:
                printw("Please input the address you wish to use for the server bind:\n");
                scanw("%16s",chosen_address);
                refresh();
                break;
            case 3:

                break;
            default:
                break;
        }

    }
    return chosen_address;
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

char* settings_menu() {
    int loopCheck=TRUE;
    char* selected_address = malloc(INET_ADDRSTRLEN); //either ipv4 or ipv6 but max size is ipv6

    initscr();
    attron(A_BOLD);;
    printw("#       #   ######   #    #   #    #\n");
    printw("##     ##   #        ##   #   #    #\n");
    printw("# #   # #   ######   # #  #   #    #\n");
    printw("#  # #  #   #        #  # #   #    #\n");
    printw("#   #   #   ######   #   ##    ####\n\n\n");
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
                break;
            case SET_HOST_IP:
                wclear(stdscr);
                wrefresh(stdscr);
                selected_address = setHostAddress(stdscr);
                getch();
                break;
            case 3:
                //TODO
                //Going to add more setup menu options for user
                break;
            case EXIT_MENU:
                loopCheck = FALSE;
            default:
                break;
        }
        wclear(stdscr);
        wrefresh(stdscr);
    }
    endwin();
    return selected_address;
}
*/


/*static const cyaml_schema_value_t yaml_settings_parser() {
    //TODO
}*/