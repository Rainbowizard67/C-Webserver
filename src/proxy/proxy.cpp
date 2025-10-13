#include "../include/proxy.hpp"

namespace ScurryProxy {
    
    class ProxyEventLoop {
    public:
        ProxyEventLoop() {

        }

        void StartEventLoop(int epoll_fd, int server_soc) {

        }
            


    }
    
    
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
}