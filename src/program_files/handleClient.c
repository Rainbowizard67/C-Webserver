#include "../headers/handleClient.h"

// static function prototypes
static void parse_HTTP_request(const char* request);
// end static function prototypes

void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size) {
    
    char* recv_buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));

    if(recv_buffer == NULL) {
        perror("Error allocating memory: ");
        return;
    }

    int bytes_read = recv(soc, recv_buffer, BUFFER_SIZE, 0);
    if(bytes_read == -1) {
        perror("Error receving client request: ");
        return;
    }
    if(bytes_read == 0) {
        printf("Client closed the connection\n");
        return;
    }
    printf("Received request:\n%s\n", recv_buffer);

    parse_HTTP_request(recv_buffer);

    free(recv_buffer);

    char* message = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "<head><titl>Hello mom!</title></head>\n"
        "<body>\n"
        "<h1>Hello, family!</h1>\n"
        "</body>\n"
        "</html>\n";

    int bytes_sent = send(soc, message, strlen(message), 0);

    if(bytes_sent < 0) {
        close(soc);
        perror("Error with sending message: ");
        return;
    }

}

void http_404_response() {
    
}

static void parse_HTTP_request(const char* request) {
    char method[10] = {0}, url[1024] = {0}, version[20] = {0};
    
    if(sscanf(request, "%9s %1023s %19s", method, url, version) != 3) {
        printf("Invalid request line\n");
        return;
    }

    const char* headers = strstr(request, "\r\n");
    if(headers) {
        headers += 2;
    }
        
    const char* body = strstr(headers, "\r\n\r\n");
    if(body) {
        body += 4;
        if(*body) {
            printf("Request body: %s\n", body);
        }
        else {
            printf("No request body found\n");
        }
    }


    printf("Method: %s\n", method);
    printf("URL: %s\n", url);
    printf("Version: %s\n", version);
}






