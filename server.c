#include"server.h"


int main(int argc, char *argv[]) {
    struct sockaddr_in serverAddress; //structure for server socket interface

    socklen_t addrlen = sizeof(serverAddress); //socklen_t=unsigned int, size of the serverAddress struct

    int socClient; //client socket

    int ipAdd = ""; //local Ipv4 address used to bind for the server socket

    int socIpv4 = socket(AF_INET, SOCK_STREAM, 0); //server socket
    //socket(int domain, int type, int protocol)

    if (socIpv4 == -1) {
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //creates the socket, socketfd = socket(domain, type, protocol);

    //struct setup
    memset(&serverAddress, 0, addrlen); //sets the struct in memory all to the value of zero
    serverAddress.sin_family = AF_INET; //sets the address family
    serverAddress.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)

    if (inet_pton(AF_INET, ipAdd, &serverAddress.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAddress struct
        close(socIpv4); //0 is no valid address, 1 is success, and -1 is a fail
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if  (bind(socIpv4, serverAddress.sin_addr.s_addr, addrlen) == -1) { //binds the ip address to the socket so that they are synonymous
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socIpv4, backlog) == -1) { //listens for the client socket
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //listen(socketfd, backlog);

    while (true) {
        if (listen(socIpv4, backlog) == -1) { //listens for the client socket
        close(socIpv4);
        exit(EXIT_FAILURE);
        } //listen(socketfd, backlog);

        if ((socClient = accept(socIpv4, &serverAddress.sin_addr.s_addr, &addrlen)) < 0) { //accepts clients to the server from the listen backlog connection request list
            perror("No clients dectected yet\n");
            continue;
        } //accept(socketfd, addr, addrlen);

        //TO DO, do send and receive data for just one user before attempting multithreading or Select


    }

    close(socIpv4); //closes the socket file descriptor

    return 0;
}
