#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdbool.h>


int main() {
    
    while(true) {
        int endpoint = socket(AF_INET, SOCK_STREAM, 0);

        int endpoint = socket(AF_INET6, SOCK_STREAM, 0);

        listen(endpoint, 100);

    }

    return 0;
}
