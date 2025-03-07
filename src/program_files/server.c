#include "../headers/server.h"
/*Main server program, where the starting point is.
This is an HTTP 1.0 server written in C and is subject to changes/updates in the future.*/

//This function populates & returns the sockaddr_in struct and binds the selected IP from the net_menu, as well as starting to listen on the socket pointer.
sockaddr_in set_server_interface(int socServ, char* ipAdd, socklen_t addrlen) {
        
    sockaddr_in serverAdd; //struct for server socket interface

    addrlen = sizeof(serverAdd);

    //socket(int domain, int type, int protocol)
    socServ = socket(AF_INET, SOCK_STREAM, 0);

    if (socServ == -1) {
        close(socServ);
        perror("Error creating socket FD: ");
        exit(EXIT_FAILURE);
    }

    //struct setup
    memset(&serverAdd, 0, addrlen); //sets the struct in memory all to the value of zero
    serverAdd.sin_family = AF_INET; //sets the address family
    serverAdd.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)
    serverAdd.sin_addr.s_addr = INADDR_ANY; //sets the address to any so before you actually input the real address it is assigned a zeroed input

    //ipAdd = net_menu(); //local Ipv4 used to bind for the server socket
    ipAdd = "127.0.0.1";

    if(inet_pton(AF_INET, ipAdd, &serverAdd.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAdd struct
        close(socServ);
        perror("Error storing or translating address: ");
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if(bind(socServ, (struct sockaddr *)&serverAdd, addrlen) == -1) { //binds the ip address to the socket so that they are synonymous
        close(socServ);
        perror("Error binding server address to socket: ");
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socServ, BACKLOG) == -1) { //listens for the client socket
        close(socServ);
        perror("Error listening on server socket: ");
        exit(EXIT_FAILURE);
    } //listen(socketfd, backlog);

    printf("webserver: Waiting for connections on port %d\n", PORT);

    return serverAdd;
}

int main(int argc, char *argv[]) {
    int socServer, socClient; 
    struct sockaddr_storage client_addr;
    char ip[INET_ADDRSTRLEN];
    socklen_t addrlen;
    
    sockaddr_in server = set_server_interface(socServer, ip, addrlen); //returns the server interface

    //main program loop to accept and handle clients
    while(true) {
        socklen_t sin_size = sizeof(client_addr);
        if ((socClient = accept(socServer, (struct sockaddr*)&client_addr, &sin_size)) < 0) { //accepts clients to the server from the listen backlog connection request list
            continue;
        }

        handle_client(socClient, client_addr, sin_size);
    }


    close(socServer);

    free(ip);

    return 0;
}
