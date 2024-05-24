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

int main() {
    
    int socIpv4 = socket(AF_INET, SOCK_STREAM, 0); //creates the socket, socketfd = socket(domain, type, protocol);
    if (socIpv4==-1) {
        EXIT_FAILURE;
    }

    

    if(bind(socIpv4, , ) == -1) {

    }





    while(true) {

        if (listen(socIpv4, backlog) == -1) {
            close(socIpv4);
            EXIT_FAILURE;
        } //listens for client socket, listen(socketfd, backlog);

    }

    return 0;
}
