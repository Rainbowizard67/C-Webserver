#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdbool.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define backlog 50

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

    int ipAdd = "192.168.10.120";

    int socIpv4 = socket(AF_INET, SOCK_STREAM, 0); //creates the socket, socketfd = socket(domain, type, protocol);

    if (socIpv4==-1) {
        exit(EXIT_FAILURE);
    }

    memset(&serverAddress, 0, sizeof(serverAddress)); //sets the struct in memory all to the value of zero

    serverAddress.sin_family = AF_INET;
    
    serverAddress.sin_port = htons(8080); //htons converts the int to network byte order (from the 8080 to the actual port)
    
    if (inet_pton(AF_INET, ipAdd, &serverAddress.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAddress struct
        close(socIpv4);
        exit(EXIT_FAILURE);
    }

    

    

    if(bind(socIpv4, , sizeof(serverAddress)) == -1) {

    }



    while(true) {

        if (listen(socIpv4, backlog) == -1) {
            close(socIpv4);
            EXIT_FAILURE;
        } //listens for client socket, listen(socketfd, backlog);

        accept(socIpv4,)

    }

    close(socIpv4); //closes the socket file descriptor

    return 0;
}
