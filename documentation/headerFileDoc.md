This is comprehensive list of the header files used in this project.
As well as which specific functions, variables, structs, and data structures are used under each header file.

C Standard Library (no explaination needed):
    -<stdio.h>
    -<stdlib.h>
    -<stdbool.h>
    -<string.h>

POSIX Library:
    -<sys/socket.h>
    -<sys/un.h>
    -<netinet/in.h>
    -<arpa/inet.h>
    -<unistd.h>
    -<pthread.h>



##<sys/socket.h>##
    Summary: POSIX standard header file that provides definitions and declarations for socket/network programming

        Socket Types (Macros):
            - 'SOCK_STREAM': Byte-stream socket, multiplex, connection-based, ex: TCP
            - 'SOCK_DGRAM': Datagram socket, connectionless, unreliable messages, ex: UDP
            - 'SOCK_RAW': Raw network protocol access
        
        Address Families (Macros):
            - 'AF_INET': IPv4 address family, 
            - 'AF_INET6': IPv6 address family,
            - 'AF_UNIX': local communication address family,
        
        Socket structures (Structs):
            - 'struct sockaddr': Generic socket address structure
            - 'struct sockaddr_in': 
            - 'struct sockaddr_in6':
            - 'struct sockaddr_un':