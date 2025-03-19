#include "../headers/handleClient.h"

// static function prototypes
static void parse_HTTP_request(const char* request, int soc);
static void get_HTTP_request(int soc);
static void http_404_response();
// end static function prototypes

void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size) {
    
    //This is the keep alive option so that the connection stays open
    int enable = 1;
    if(setsockopt(soc, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable)) < 0) {
        perror("Error setting socket option: ");
        return;
    }

    //This is the timeout for the send and recv sections
    //we are going to move this later when we understand our program more
    struct timeval timeout;
    timeout.tv_sec = 10; //seconds
    timeout.tv_usec = 0; //microseconds
    setsockopt(soc, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(soc, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    while(true) {

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

        parse_HTTP_request(recv_buffer, soc);

        free(recv_buffer);
    }
}

static void http_404_response() {
    
}

static void parse_HTTP_request(const char* request, int soc) {
    char method[10] = {0}, url[1024] = {0}, version[20] = {0};
    
    if(sscanf(request, "%9s %1023s %19s", method, url, version) != 3) {
        printf("Invalid request line\n");
        return;
    }

    const char* headers = strstr(request, "\r\n");
    if(headers) {
        headers += 2;
    }

    int content_length = -1;
    const char* body = NULL;

    const char* content_length_header = strstr(headers, "Content-Length:");
    if (content_length_header) {
        sscanf(content_length_header, "Content-Length: %d", &content_length);
    }
    
    body = strstr(headers, "\r\n\r\n");
    if(body) {
        body += 4;
    }

    //body data can be dynamically allocated with the content-length in some of the HTTP methods
    if(strcmp(method, "GET") == 0) {
        get_HTTP_request(soc);
    }
    else if(strcmp(method, "POST") == 0) {

    }
    else if(strcmp(method, "PUT") == 0) {

    }
    else if(strcmp(method, "PATCH") == 0) {

    }
    else if (strcmp(method, "DELETE") == 0) {

    }
    else if (strcmp(method, "HEAD") == 0) {

    }
    else if (strcmp(method, "OPTIONS") == 0) {

    }
    else if (strcmp(method, "TRACE") == 0) {

    }
    else if (strcmp(method, "CONNECT") == 0) {

    }
}

static void get_HTTP_request(int soc) {
    char* message = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: keep-alive\r\n"
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






