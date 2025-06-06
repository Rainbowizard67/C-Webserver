#include "../include/settings.h"

//Start structure settings
struct handler_settings {
    char doc_root[MAX_FILEPATH_SIZE];
    char default_path[MAX_FILEPATH_SIZE];
    unsigned short keep_alive;
    //TODO, default timeout
};

typedef struct handler_settings handler_settings_t;

struct network_settings {
    unsigned short port_number;
    char ipv4_address[16];
    unsigned short backlog;
    unsigned short max_events;
};

typedef struct network_settings network_settings_t;

struct settings {
    network_settings_t* network;
    handler_settings_t* handler;
};
typedef struct settings settings_t;
//End structure settings

//Start CYAML schema settings and format
static const cyaml_schema_field_t ns_fields_schema[] = {
    CYAML_FIELD_UINT("Port_Number", CYAML_FLAG_DEFAULT, network_settings_t, port_number),
    CYAML_FIELD_STRING("IPv4_Address", CYAML_FLAG_DEFAULT, network_settings_t, ipv4_address, 0),
    CYAML_FIELD_UINT("Backlog", CYAML_FLAG_DEFAULT, network_settings_t, backlog),
    CYAML_FIELD_UINT("Max_Events", CYAML_FLAG_DEFAULT, network_settings_t, max_events),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t hs_fields_schema[] = {
    CYAML_FIELD_STRING("Doc_Root", CYAML_FLAG_POINTER, handler_settings_t, doc_root, 0),
    CYAML_FIELD_STRING("Default_Path", CYAML_FLAG_POINTER, handler_settings_t, default_path, 0),
    CYAML_FIELD_UINT("Keep_Alive", CYAML_FLAG_DEFAULT, handler_settings_t, keep_alive),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t setting_fields_schema[] = {
    CYAML_FIELD_MAPPING("Network", CYAML_FLAG_POINTER, settings_t, network, ns_fields_schema),
    CYAML_FIELD_MAPPING("Handler", CYAML_FLAG_POINTER, settings_t, handler, hs_fields_schema),
    CYAML_FIELD_END
};

static const cyaml_schema_value_t schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, settings_t, setting_fields_schema),
};
//End CYAML schema settings and format

//Initialization of the data from the structs into the hash table
static hashTable_t* init_hashtable(settings_t* s) {
    hashTable_t* ht = create_table(HT_SIZE);
    
    insert(ht, "doc_root", s->handler->doc_root, strlen(s->handler->doc_root) + 1);
    insert(ht, "default_path", s->handler->default_path, strlen(s->handler->default_path) + 1);
    insert(ht, "keep_alive", &(s->handler->keep_alive), sizeof(s->handler->keep_alive));
    
    insert(ht, "port_number", &(s->network->port_number), sizeof(s->network->port_number));
    insert(ht, "ipv4_address", s->network->ipv4_address, strlen(s->network->ipv4_address) + 1);
    insert(ht, "backlog", &(s->network->backlog), sizeof(s->network->backlog));
    insert(ht, "max_events", &(s->network->max_events), sizeof(s->network->max_events));

    return ht;
}

//Loads yaml into structures then passes structures to hash table init
static hashTable_t* load_yaml(char* filepath) {
    const cyaml_config_t config = {
        .log_level = CYAML_LOG_DEBUG,
        .log_fn = cyaml_log,
        .mem_fn = cyaml_mem,
        .log_level = CYAML_LOG_WARNING,
    };

    settings_t* s = NULL;

    cyaml_err_t err = cyaml_load_file(filepath, &config, &schema, (void **)&s, NULL);

    if(err != CYAML_OK) {fprintf(stderr, "CYAML load error: %s\n", cyaml_strerror(err)); exit(EXIT_FAILURE);};

    if(s == NULL) {fprintf(stderr, "CYAML failed: settings pointer is NULL\n"); exit(EXIT_FAILURE);}

    hashTable_t* htable = init_hashtable(s);

    err = cyaml_free(&config, &schema, s, 0);

    if(err != CYAML_OK) {fprintf(stderr, "CYAML free error: %s\n", cyaml_strerror(err)); exit(EXIT_FAILURE);};

    return htable;
}

//General settings function that starts initialization of everything
hashTable_t* main_settings(char* fp) {

    char* filepath = "/home/alexrob67/C-Webserver/config/wsconfig.yaml";

    if(access(filepath, F_OK) != 0) {printf("Error config file does not exist!\n"); exit(EXIT_FAILURE);}
    
    return load_yaml(filepath);
}

//Wrapper function to make output look better using settings data
void* get_value(hashTable_t* ht, char* key) {
    return search(ht, key);
}

//Wrapper function to make program look better when freeing
void free_settings(hashTable_t* ht) {
    free_table(ht);
}