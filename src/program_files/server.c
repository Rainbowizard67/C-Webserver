/*
    Main server program, where the starting point is.
    This is an HTTP 1.0 server written in C and is subject to changes/updates in the future.
*/

#include "headers/server.h"

/*NOTES: 
    -macros are defined in the header file
*/

//data types
typedef struct sockaddr_in sockaddr_in;
//end data types

void handle_client() {
    
}

/*
This function populates & returns the sockaddr_in struct and binds the selected IP
from the net_menu, as well as starting to listen on the socket pointer.
*/
sockaddr_in make_server_interface(int socServ, char* ipAdd, socklen_t addrlen) {
        
    sockaddr_in serverAdd; //struct for server socket interface

    addrlen = sizeof(serverAdd);

    ipAdd = net_menu(); //local Ipv4 used to bind for the server socket

    //socket(int domain, int type, int protocol)
    int socIpv4 = socket(AF_INET, SOCK_STREAM, 0);

    if (socIpv4 == -1) {close(socIpv4); exit(EXIT_FAILURE);}

    //struct setup
    memset(&serverAdd, 0, addrlen); //sets the struct in memory all to the value of zero
    serverAdd.sin_family = AF_INET; //sets the address family
    serverAdd.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)
    serverAdd.sin_addr.s_addr = INADDR_ANY; //sets the address to any so before you actually input the real address it is assigned a zeroed input

    if(inet_pton(AF_INET, ipAdd, &serverAdd.sin_addr.s_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAdd struct
        close(socIpv4); //0 is no valid address, 1 is success, and -1 is a fail
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if(bind(socServ, (struct sockaddr *)&serverAdd, addrlen) == -1) { //binds the ip address to the socket so that they are synonymous
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socServ, backlog) == -1) { //listens for the client socket
        close(socServ);
        exit(EXIT_FAILURE);
        } //listen(socketfd, backlog);

    return serverAdd;
}

int main(int argc, char *argv[]) {
    int socServer, socClient;
    char ip[INET_ADDRSTRLEN];
    socklen_t addrlen;
    
    sockaddr_in server = make_server_interface(socServer, ip, addrlen); //returns the server interface

    while(true) {


        if ((socClient = accept(socServer, (struct sockaddr*)&server, &addrlen)) < 0) { //accepts clients to the server from the listen backlog connection request list
            perror("No clients dectected yet\n");
            continue;
        } //accept(socketfd, addr, addrlen);

        //TO DO, do send and receive data for just one user before attempting multithreading or Select


    }

    close(socServer); //closes the socket ptr

    return 0;
}
