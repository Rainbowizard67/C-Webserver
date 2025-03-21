#include "../headers/handleClient.h"

// static function prototypes
static void parse_HTTP_request(const char* request, int soc);
static int get_HTTP_request(int soc, char* URL);
static void http_404_response();
// end static function prototypes

void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size) {

    //This is the timeout for the send and recv sections
    //we are going to move this later when we understand our program more
    /*struct timeval timeout;
    timeout.tv_sec = 10; //seconds
    timeout.tv_usec = 0; //microseconds
    setsockopt(soc, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(soc, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));*/

    while(true) {

        char* recv_buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));

        if(recv_buffer == NULL) {
            perror("Error allocating memory: ");
            return;
        }

        int bytes_read = recv(soc, recv_buffer, MAX_BUFFER_SIZE, 0);
        if(bytes_read == -1) {
            perror("Error receving client request: ");
            free(recv_buffer);
            return;
        }
        if(bytes_read == 0) {
            printf("Client closed the connection\n");
            free(recv_buffer);
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
        get_HTTP_request(soc, url);
        return;
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

static int get_HTTP_request(int soc, char* URL) {
    file_data_t* fd = file_load("/home/alexrob67/C-Webserver/src/web_pages/example.html");

    if(fd == NULL) {
        return -1;
    }

    char* message = (char*)malloc(fd->size + MAX_BUFFER_SIZE);

    if(message == NULL) {
        file_free(fd);
        return -1;
    }

    int header_len = snprintf(message, MAX_BUFFER_SIZE,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: Keep-Alive\r\n"
        "\r\n", 
        fd->size);
    
    memcpy(message + header_len, fd->data, fd->size);

    file_free(fd);

    int bytes_sent = send(soc, message, header_len + fd->size, 0);

    if(bytes_sent < 0) {        
        perror("Error with sending message: ");
        free(message);
        return -1;
    }

    free(message);

    return 0;    
}






