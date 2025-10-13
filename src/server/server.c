#include "../include/server.h"
/*========================================================
| This portion is a web server written in C. Servers     |
| static web pages and then sends them through the proxy |
=========================================================*/


//Sets the socket to nonblocking mode so that the program does not pause during I/O
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

//Main listening loop and accepting loop for clients
void main_event_loop(int epoll_fd, int server_soc) {
    object_pool_t* op = create_pool(50);
    tpool_t* tp = tpool_create(6);
    int max_events = get_fd_limit();
    
    struct epoll_event* events = malloc(sizeof(struct epoll_event) * max_events);
    if (!events) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char ip[INET_ADDRSTRLEN];
    
    while(!stop) {
        int num_events = epoll_wait(epoll_fd, events, max_events, -1);
        
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

                client_connection_t* client_conn = borrow_object(op);

                if(client_conn == NULL) {
                    fprintf(stderr, "Failed to allocate client conn\n");
                    exit(EXIT_FAILURE);
                }

                client_conn->client_len = sizeof(client_conn->client_addr);

                if(getpeername(events[i].data.fd, (struct sockaddr*)&client_conn->client_addr, &client_conn->client_len)) {
                    printf("Error receiving client info\n");
                    free(client_conn);
                    exit(EXIT_FAILURE);
                } //gets connected client info

                client_conn->client_socket = events[i].data.fd;
                client_conn->state = STATE_READ;

                if(THREAD_THRESHOLD < active_requests) {
                    if(!(tpool_add_work(tp, (void*)http_client_handler, (void*)client_conn))) {
                        continue;
                    }
                }
                else {
                    http_client_handler(client_conn);
                }

                return_object(op, client_conn);

                active_requests--;
            }
        }
    }
    free(events);
    destroy_pool(op);
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
        close(epoll_fd);
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

    //socket option to allow address and port reuse
    int opt = 1;
    if(setsockopt(socServ, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
	    perror("setsockopt error");
	    exit(EXIT_FAILURE);
    }

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

