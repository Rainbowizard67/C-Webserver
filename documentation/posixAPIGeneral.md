POSIX (Portable Operating System Inteface)

https://www.gnu.org/software/libc/manual/html_node/POSIX.html

Summary:
    The POSIX Unix library is a standard for OS interface and OS environment to support portability of applications at a low level. Works with the standard GNU C libaray.

Key components:
    1: Process Management
        -fork()
        -exec()
        -wait()
    2: File and Directory Operations
        -open(), close(), read(), write()
        -stat()
        -mkdir(), rmdir()
        -opendir(), readdir(), closedir()
    3: I/O Operations
        -select()
        -poll()
    4: Inter-Process Communication (IPC)
        -pipe()
        -shmget(), shmat(), shmdt()
        -semget(), semop(), semctl()
        -msgget(), msgsnd(), msgrcv(), etc
    5: Signal Handling
        -signal()
        -kill()
        -sigaction()
    6: Thread Management
        -pthread_create(), pthread_join()
        -pthread_mutex_init(), etc
        -pthread_cond_wait(), etc
    7: Network Communication
        -socket(), bind(), listen(), accept()
        -connect(), send(), recv()
    8: Time and Date
        -time(), ctime()
        -gettimeofday(), settimeofday()
    9: Environment
        -getenv(), setenv()
        -getuid(), geteuid()
    10: Advanced Features
        -mmap()
        -fcntl()
        -ioctl()

All of these components form the core of the POSIX standard, 
forming portability across Unix or Unix like (Linux) operating systems.

For more general POSIX information follow the link at the top.

