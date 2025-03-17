#include "../headers/handleClient.h"


void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size) {
    
    char buffer[BUFFER_SIZE];

    int bytes_read = recv(soc, buffer, BUFFER_SIZE, 0);
    if(bytes_read == -1) {
        perror("Error receving client request: ");
        return;
    }
    if(bytes_read == 0) {
        printf("Client closed the connection\n");
        return;
    }
    printf("Received request:\n%s\n", buffer);

    char* message = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "<head><titl>Hello</title></head>\n"
        "<body>\n"
        "<h1>Hello, World!</h1>\n"
        "</body>\n"
        "</html>\n";

    int bytes_sent = send(soc, message, strlen(message), 0);

    if(bytes_sent < 0) {
        close(soc);
        perror("Error with sending message: ");
        return;
    }

    close(soc);
}

void http_404_response() {
}






