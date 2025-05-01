#include "../headers/server.h"
/*=======================================================================================
| This program is a web server written in C. More details 
| are below for this file:                          
|
| Functions:
|
|
|
===================================================*/

//signal check
volatile sig_atomic_t stop;

//TODO
void make_daemon(void) {
    //this function will not be created/worked on until handleClient, threads are implemented, settings is complete, YAML parser, etc.
}

//TODO
bool parse_args(int* argc, char* argv[]) {
    if(*argc > 2) {
        printf("webserver: too many args\n");
        return false;
    }
    /*if(sizeof(argv[1]) > MAX_FILEPATH_SIZE) {
        printf("webserver: over max string size\n");
        return false;
    }*/
    
    return true;
}

//Handling Ctrl+C (stopping the server in the terminal)
void handle_sigint(int sig) {
    stop = 1;
}

//Sets the socket to nonblocking mode so that the program does not pause during I/O
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

//Main listening loop and accepting loop for clients
void main_event_loop(int epoll_fd, int server_soc) {
    tpool_t* tp = tpool_create(MAX_POOL_SIZE);
    struct epoll_event events[MAX_EVENTS];
    char ip[INET_ADDRSTRLEN];
    
    while(!stop) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        
        if(num_events < 0) {
            if(errno == EINTR) {
                continue;
            }
            perror("Error with epoll_wait: ");
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<num_events; i++) {
            if(events[i].data.fd == server_soc) {
                struct sockaddr_storage client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_soc = accept(server_soc, (struct sockaddr*)&client_addr, &client_len);
                if(client_soc < 0) {
                    perror("Error with accepting client: ");
                    continue;
                }

                inet_ntop(client_addr.ss_family, &((struct sockaddr_in*)&client_addr)->sin_addr, ip, INET_ADDRSTRLEN);
                printf("webserver: accepted connection from %s\n", ip);

                set_nonblocking(client_soc);

                struct epoll_event ev;
                ev.data.fd = client_soc;
                ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;

                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_soc, &ev) < 0) {
                    perror("Error with with adding client socket to events: ");
                    close(client_soc);
                    exit(EXIT_FAILURE);
                }             
            }
            else {
                active_requests++;

                client_request_t* request = (client_request_t*)malloc(sizeof(client_request_t));

                if(getpeername(events[i].data.fd, (struct sockaddr*)&request->client_addr, &request->client_len)) {
                    printf("Error receiving client info\n");
                    free(request);
                    exit(EXIT_FAILURE);
                } //gets connected client info

                request->client_socket = events[i].data.fd;
                request->state = STATE_READ;

                if(active_requests > THREAD_THRESHOLD) {
                    tpool_add_work(tp, (thread_func_t)http_client_handler, request);
                }
                else {
                    http_client_handler(request);
                }

                active_requests--;
            }
        }
    }
    tpool_destroy(tp);
    printf("\nwebserver: exiting program...\n");
}

//Creates the multiplexing event structure on the server interface
int set_epoll_events(struct epoll_event ev, int socServer) {
    int epoll_fd = epoll_create1(0);
    if(epoll_fd < 0) {
        perror("Error creating epoll: ");
        close(socServer);
        exit(EXIT_FAILURE);
    }
    ev.events = EPOLLIN;
    ev.data.fd = socServer;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socServer, &ev) < 0) {
        perror("Error adding socket to epoll: ");
        exit(EXIT_FAILURE);
    }

    return epoll_fd;
}

//Sets the server interface (ip, port, and socket)
int set_server_interface(char* ipAdd, socklen_t addrlen) {
    int socServ;

    sockaddr_in serverAdd; //struct for server socket interface

    addrlen = sizeof(serverAdd);

    //socket(int domain, int type, int protocol)
    socServ = socket(AF_INET, SOCK_STREAM, 0);

    if (socServ < 0) {
        close(socServ);
        perror("Error creating socket FD: ");
        exit(EXIT_FAILURE);
    }

    //socket option to allow address reuse
    int opt=1;
    setsockopt(socServ, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //struct setup
    memset(&serverAdd, 0, addrlen); //sets the struct in memory all to the value of zero
    serverAdd.sin_family = AF_INET; //sets the address family
    serverAdd.sin_port = htons(PORT); //htons converts the int to network byte order (from the 8080 to the actual port)
    //serverAdd.sin_addr.s_addr = INADDR_ANY; //sets the address to any so before you actually input the real address it is assigned a zeroed input

    //local Ipv4 used to bind for the server socket (will add a call for settings later)
    strcpy(ipAdd, "127.0.0.1");

    if(inet_pton(AF_INET, ipAdd, &serverAdd.sin_addr) <= 0) { //converts the text rep of Ipv4 address to the binary form, it is then stored in the serverAdd struct
        close(socServ);
        perror("Error storing or translating address: ");
        exit(EXIT_FAILURE);
    } //inet_pton(addressFamily, src, networkAddrStruct);

    if(bind(socServ, (struct sockaddr *)&serverAdd, addrlen) < 0) { //binds the ip address to the socket so that they are synonymous
        close(socServ);
        perror("Error binding server address to socket: ");
        exit(EXIT_FAILURE);
    } //bind(socketfd, addr, addrlen);

    if (listen(socServ, BACKLOG) < 0) { //listens for the client socket
        close(socServ);
        perror("Error listening on server socket: ");
        exit(EXIT_FAILURE);
    } //listen(socketfd, backlog);

    set_nonblocking(socServ);

    printf("webserver: Waiting for connections on port %d and address %s\n", PORT, ipAdd);

    return socServ;
}

//Freeing settings data, multiplexing event (epoll), and server interface
void clean_program(int ep_fd, int soc, hashTable_t* ht) {
    //free_settings(ht);
    
    close(soc);
    close(ep_fd);
}

//Main function
int main(int argc, char *argv[]) {

    signal(SIGINT, handle_sigint);

    if(!(parse_args(&argc, argv))) {exit(EXIT_FAILURE);}
    
    //hashTable_t* ht = main_settings(argv[1]);
    
    //Start server socket init (returns socket fd)
    char ip[INET_ADDRSTRLEN];
    socklen_t addrlen;    
    int socServer = set_server_interface(ip, addrlen);
    //End server socket init

    //Start Epoll events init
    struct epoll_event ev;
    int epoll_fd = set_epoll_events(ev, socServer);
    //End Epoll events init

    //Start main program
    main_event_loop(epoll_fd, socServer);

    clean_program(epoll_fd, socServer, NULL);
    //End main program

    printf("bye");
    return 0;
}
