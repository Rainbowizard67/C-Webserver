#include "../include/handleClient.h"

// static function prototypes
static bool parse_HTTP_request(const char* request, int soc);
static int get_HTTP_request(int soc, char* URL);
static void http_404_response(int soc);
// end static function prototypes

void http_client_handler(client_connection_t* request) {
    //timeout.tv_sec = 10;

    size_t total_bytes_recv = 0;

    bool running = true;
    while(running) {
        switch(request->state) {
            case STATE_READ: {
                size_t bytes_read = recv(request->client_socket, request->buffer, MAX_BUFFER_SIZE, 0);
                if(bytes_read == -1) {
                    if(errno == EAGAIN || errno == EWOULDBLOCK) {
                        return;
                    }
                    else {
                        perror("Error receiving client request: ");
                        request->state = STATE_CLOSE;
                    }
                }
                else if(bytes_read == 0) {
                    printf("Client closed the connection\n");
                    request->state = STATE_CLOSE;
                }
                else {
                    total_bytes_recv += bytes_read;
                    request->buffer[total_bytes_recv] = '\0';
                    printf("Received request:\n%s\n", request->buffer);
                    request->state = STATE_PARSE;
                }
                break;
            }
            case STATE_PARSE:
                bool check = parse_HTTP_request(request->buffer, request->client_socket);
                if(!check) {
                    request->state = STATE_CLOSE;
                }
                else {
                    request->state = STATE_READ;
                }
                break;
            case STATE_CLOSE:
                running = false;
                break;
        }
        //TODO, check for keep alive and inactivity(timeout)
    }

    close(request->client_socket);
    free(request);
}

static void http_404_response(int soc) {
    char* file_404 = "/home/alexrob67/C-Webserver/src/web_pages/example_404.html";

    file_data_t* fd = file_load(file_404);

    if(fd == NULL) {
        file_free(fd);
        return;
    }
       
    char* message = (char*)malloc(fd->size + MAX_BUFFER_SIZE);

    if(message == NULL) {
        file_free(fd);
        return;
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
        return;
    }

    free(message);
}

static bool parse_HTTP_request(const char* request, int soc) {
    char method[10] = {0}, url[1024] = {0}, version[20] = {0};
    
    if(sscanf(request, "%9s %1023s %19s", method, url, version) != 3) {
        printf("Invalid request line\n");
        return false;
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
        return true;
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
    char* get_file = NULL;
    const char* default_path = strcat(d_web_path, "/example.html");

    //If the default_path or path in just does not exist we must send a 404
    if((strcmp(URL, "/")) == 0) {
        get_file = strdup(default_path);
    }
    else {
        get_file = (char*)malloc(strlen(URL) * sizeof(char) + 1);
        if(get_file) strcpy(get_file, URL);
    }

    if(get_file == NULL) return -1;

    file_data_t* fd = file_load(get_file);

    free(get_file);

    if(!fd || !fd->data) {
        http_404_response(soc);
        return -1;
    }

    int header_len = snprintf(NULL, 0, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: Keep-Alive\r\n"
        "\r\n", 
        fd->size);

    char* message = (char*)malloc(fd->size + header_len + 1);

    if(message == NULL) {
        file_free(fd);
        return -1;
    }

    snprintf(message, header_len + 1,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: Keep-Alive\r\n"
        "\r\n", 
        fd->size);
    
    memcpy(message + header_len, fd->data, fd->size);

    int bytes_sent = send(soc, message, header_len + fd->size, 0);

    if(bytes_sent < 0) {        
        perror("Error with sending message: ");
        free(message);
        file_free(fd);
        return -1;
    }

    free(message);
    file_free(fd);

    return 0;    
}






