#include "include/scurry_main.hpp"

// Handling SIGINT
__attribute__((constructor))
void handle_sigint(int sig) {
    stop = 1;
}

int main() {
    signal(SIGINT, handle_sigint);


    return 0;
}