This is comprehensive list of the header files used in this project.

As well as which specific functions, variables, structs, and data structures are used under each header file.

If any functions, Macros, etc. appear in multiple header files that will be only shown once.


C Standard Library (no explaination needed):
    -<stdio.h>
    -<stdlib.h>
    -<stdbool.h>
    -<string.h>

POSIX Library:
    -<sys/socket.h>
    -<netinet/in.h>
    -<arpa/inet.h>
    -<unistd.h>
    -<pthread.h>


##<sys/socket.h>##
    Summary: POSIX standard header file that provides general definitions and declarations for socket/network programming.

        Socket Types (Macros):
            - 'SOCK_STREAM': Byte-stream socket, multiplex, connection-based, ex: TCP
            - 'SOCK_DGRAM': Datagram socket, connectionless, unreliable messages, ex: UDP
            - 'SOCK_RAW': Raw network protocol access
        
        Address Families (Macros):
            - 'AF_INET': IPv4 address family
            - 'AF_INET6': IPv6 address family
            - 'AF_UNIX': local communication address family
        
        Socket structures (Structs):
            - 'struct sockaddr': Generic socket address structure
            - 'struct sockaddr_in': IPv4 socket address structure
            - 'struct sockaddr_in6': IPv6 socket address structure
            - 'struct sockaddr_un': Unix domain socket structure
        
        Macros:
            - 'SO_REUSEADDR': Allows the socket to be bound to an address that is use already
            - 'SOCK_NOBLOCK': Sets socket to non-blocking
        
        Functions:
            - 'socket()':
            - 'bind()':
            - 'listen()':
            - 'accept()':
            - 'connect()':
            - 'send()', 'sendto()', 'sendmsg()':
            - 'recv()', 'recvfrom()', 'recvmsg()':
            - 'close()':
            - 'setsockopt()', 'getsockopt()':

##<netinet/in.h>##
    Summary: POSIX standard header file that provides definitions for the internet protocol family, structures for 
    IPv4 and IPv6 addresses with communication protocols.

        Data Types and Structs:
            - 'in_addr_t':
            - 'in_port_t':
            - 'in_addr':
            - 'in6_addr':
            - 'sockaddr_in':
            - 'sockaddr_in6':
        
        Macros:
            - 'INADDR_ANY':
            - 'INADDR_LOOPBACK':
            - 'INADDR_BROADCAST':
            - 'INADDR_NONE':

        Functions:
            -'htons()':
            -'ntohs()':
            -'htonl()':
            -'ntonl()':
            -'inet_aton()':
            -'inet_ntoa()':
            -'inet_pton()':
            -'inet_ntop()':

##<arpa/inet.h>##
    Summary: POSIX standard header file that provides conversion between network/host byte order on
    different computer architecture and manipulating IP addresses. 

        Functions:
            -'





##<unistd.h>##
    Summary: POSIX standard header file that provides access to various POSIX OS API functions


##<pthread.h>##
    Summary:

