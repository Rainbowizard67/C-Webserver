#include "../include/defaults.h"


char* get_default_web_path(void) {
    if(chdir("../web_pages") != 0) {
        return NULL;
    }
    return get_working_dir();
}

char* get_default_script_path(void) {
    if(chdir("../../config") != 0) {
        return NULL;
    }
    return get_working_dir();
}

char* get_working_dir(void) {
    char* cwd = malloc(MAX_PATH);
    if(cwd == NULL) return NULL;

    if(getcwd(cwd, MAX_PATH) != NULL) {
        return cwd;
    }
    free(cwd);
    return NULL;
}