#include "../headers/settings.h"

struct handler_settings {
    const char* doc_root;
    const char* default_path;
    bool keep_alive;
};

struct network_settings {
    unsigned short port_number;
    char ipv4_address[16];
    unsigned short backlog;
    unsigned short max_events;
};

static hashTable_t* construct_ht(int size) {
    hashTable_t * ht = create_table(size);
}

void parse_yaml() {
    
}

void init_settings() {

}
