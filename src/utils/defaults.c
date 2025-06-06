#include "../include/defaults.h"

static char* get_working_dir(void) {
    char* cwd = malloc(MAX_PATH);
    if(cwd == NULL) return NULL;

    if(getcwd(cwd, MAX_PATH) != NULL) {
        return cwd;
    }
    free(cwd);
    return NULL;
}

char* get_default_web_path(void) {
    char original_dir[MAX_PATH];
    if (getcwd(original_dir, MAX_PATH) == NULL) {
        return NULL;
    }

    if (chdir("../web_pages") != 0) {
        return NULL;
    }

    char* path = get_working_dir();

    chdir(original_dir);

    return path;
}

char* get_default_config_path(void) {
    char original_dir[MAX_PATH];
    if (getcwd(original_dir, MAX_PATH) == NULL) {
        return NULL;
    }

    if (chdir("../../config") != 0) {
        return NULL;
    }

    char* path = get_working_dir();

    chdir(original_dir);

    return path;
}