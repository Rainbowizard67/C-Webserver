#include "../headers/handleClient.h"


void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size) {
    if((connect(soc, (struct sockaddr*)&client, size)) == -1) {
        close(soc);
        printf("webserver: Error connecting to client %s", client);
        return;
    }

    char buffer[BUFFER_SIZE];

    char message[] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello, welcome!\n";

    //recv(soc, buffer, BUFFER_SIZE, 0);
    //printf("Received request:\n%s\n", buffer);

    if((send(soc, message, strlen(message), 0)) == -1) {
        close(soc);
        perror("Error with sending message: ");
        exit(EXIT_FAILURE);
    }

    close(soc);
}

void http_404_response() {
    
}






