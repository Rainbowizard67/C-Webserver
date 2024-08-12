#include"server.h"

/* struct sockaddr_in {
    short int sin_family;   //Address Family (Ex: AF_INET)
    unsigned short int sin_port;    //Port number
    struct in_addr sin_addr;    //IPv4 address
    unsigned char sin_zero[8];  //Padding (zero), you do not need to set this
   };
*/

/*
    struct in_addr {
        unsigned long s_addr; //32-bit Ipv4 address in Network order
    };
*/

int main(int argc, char *argv[]) {
    struct sockaddr_in serverAddress; //sets the variable to "serverAddress" to the socket.h data type sockaddr_in, above is what the struct looks like

    socklen_t addrlen = sizeof(serverAddress); //socklen_t=unsigned int, size of the serverAddress struct

    int clientSocket;

    int ipAdd = ""; //local Ipv4 address used to bind for the server/socket

    int socIpv4 = socket(AF_INET, SOCK_STREAM, 0); //creates the socket, socketfd = socket(domain, type, protocol);

    if (socIpv4==-1) {
        exit(EXIT_FAILURE);
    }

    //next couple lines set the members of the serverAddress struct/general address structure
    memset(&serverAddress, 0, addrlen); //sets the struct in memory all to the value of zero

    serverAddress.sin_family = AF_INET; //sets the address family
    
    serverAddress.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)
    
    if (inet_pton(AF_INET, ipAdd, &serverAddress.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAddress struct
        close(socIpv4); //0 is no valid address, 1 is success, and -1 is a fail
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if(bind(socIpv4, serverAddress.sin_addr.s_addr, addrlen) == -1) { //binds the ip address to the socket so that they are synonymous
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socIpv4, backlog) == -1) { //listens for the client socket
        close(socIpv4);
        exit(EXIT_FAILURE);
    } //listen(socketfd, backlog);

    while(true) {
        if ((clientSocket = accept(socIpv4, &serverAddress.sin_addr.s_addr, &addrlen)) < 0) { //accepts clients to the server from the listen backlog connection request list
            perror("No clients dectected yet\n");
            continue;
        } //accept(socketfd, addr, addrlen);

        printf("Client accepted\n");

        //TO DO, do send and receive data for just one user before attempting multithreading or Select


    }

    close(socIpv4); //closes the socket file descriptor

    return 0;
}
