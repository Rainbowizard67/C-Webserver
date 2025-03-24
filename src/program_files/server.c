#include "../headers/server.h"
/*===================================================
| This program is a web server written in C, and a  |                             
| front end Golang terminal interface. More details |
| are below for this file:                          |
|
|
|
|
|
|
|
|
===================================================*/

void handle_sig(int sig) {
    if(sig == SIGINT) {
        printf("\nwebserver: Exiting program...\n");
        //needs to add a free/close function so that all open sockets or memory is closed before the program fully exits 
        exit(EXIT_SUCCESS);
    }
    else if(sig == SIGTSTP) {
        printf("\nwebserver: Paused program and now a background process\n");
    }
}

void make_daemon() {
    //this function will not be created/worked on until handleClient, threads are implemented, settings is complete, YAML parser, etc.
}
//This function populates & returns the sockaddr_in struct and binds the selected IP from the net_menu, as well as starting to listen on the socket pointer.
int set_server_interface(char* ipAdd, socklen_t addrlen) {
    int socServ;

    sockaddr_in serverAdd; //struct for server socket interface

    addrlen = sizeof(serverAdd);

    //socket(int domain, int type, int protocol)
    socServ = socket(AF_INET, SOCK_STREAM, 0);

    if (socServ < 0) {
        close(socServ);
        perror("Error creating socket FD: ");
        exit(EXIT_FAILURE);
    }

    //struct setup
    memset(&serverAdd, 0, addrlen); //sets the struct in memory all to the value of zero
    serverAdd.sin_family = AF_INET; //sets the address family
    serverAdd.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)
    //serverAdd.sin_addr.s_addr = INADDR_ANY; //sets the address to any so before you actually input the real address it is assigned a zeroed input

    //local Ipv4 used to bind for the server socket (will add a call for settings later)
    strcpy(ipAdd, "127.0.0.1");

    if(inet_pton(AF_INET, ipAdd, &serverAdd.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAdd struct
        close(socServ);
        perror("Error storing or translating address: ");
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if(bind(socServ, (struct sockaddr *)&serverAdd, addrlen) < 0) { //binds the ip address to the socket so that they are synonymous
        close(socServ);
        perror("Error binding server address to socket: ");
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socServ, BACKLOG) < 0) { //listens for the client socket
        close(socServ);
        perror("Error listening on server socket: ");
        exit(EXIT_FAILURE);
    } //listen(socketfd, backlog);

    printf("webserver: Waiting for connections on port %d and address %s\n", PORT, ipAdd);

    return socServ;
}

int main(int argc, char *argv[]) {
    //program signals
    signal(SIGINT, handle_sig);
    signal(SIGTSTP, handle_sig);
    //end program signals
    
    int socClient; 
    struct sockaddr_storage client_addr;
    char ip[INET_ADDRSTRLEN];
    socklen_t addrlen;
    
    int socServer = set_server_interface(ip, addrlen); //returns the server interface

    tpool_t* main_tpool = tpool_create(INIT_TPOOL_NUM);

    //main program loop to accept and handle clients
    while(true) {
        socklen_t sin_size = sizeof(client_addr);
        socClient = accept(socServer, (struct sockaddr*)&client_addr, &sin_size); //accepts clients to the server from the listen backlog connection request list
        if (socClient < 0) {
            perror("Error accepting connections: ");
            continue;
        }

        inet_ntop(client_addr.ss_family, &((struct sockaddr_in*)&client_addr)->sin_addr, ip, INET_ADDRSTRLEN);
        printf("webserver: accepted connection from %s\n", ip);

        if(!(tpool_add_work(main_tpool, http_client_handler, socClient, client_addr, sin_size))) {
           perror("Error with client_handler or t_pool: ");
        }

        //http_client_handler(socClient, client_addr, sin_size);

        close(socClient);
    }

    tpool_destroy(main_tpool);

    close(socServer);

    return 0;
}
