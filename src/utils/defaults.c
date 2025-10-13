#include "../include/scurry_utils.h"

//Gets the fd system soft limit
rlim_t get_fd_limit(void) {
    struct rlimit limit;

    if((getrlimit(RLIMIT_NOFILE, &limit) != 0)) {
        perror("Error getting fd rlimit: ");
        return 1024;
    }

    return (int)limit.rlim_cur;
}
