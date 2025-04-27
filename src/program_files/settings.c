#include "../headers/settings.h"

//Start structure settings
static struct handler_settings {
    const char* doc_root;
    const char* default_path;
    bool keep_alive;
};

typedef struct handler_settings handler_settings_t;

static struct network_settings {
    unsigned short* port_number;
    char ipv4_address[16];
    unsigned short* backlog;
    unsigned short* max_events;
};

typedef struct network_settings network_settings_t;
//End structure settings

//Start CYAML schema settings and format
static const cyaml_schema_field_t ns_fields_schema[] = {
    CYAML_FIELD_UINT_PTR("Port_Number", CYAML_FLAG_POINTER, network_settings_t, port_number),
    CYAML_FIELD_STRING_PTR("IPv4_Address", CYAML_FLAG_POINTER, network_settings_t, ipv4_address, 0, CYAML_UNLIMITED),
    CYAML_FIELD_UINT_PTR("Backlog", CYAML_FLAG_POINTER, network_settings_t, backlog),
    CYAML_FIELD_UINT_PTR("Max_Events", CYAML_FLAG_POINTER, network_settings_t, max_events),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t hs_fields_schema[] = {
    CYAML_FIELD_STRING_PTR("Doc_Root", CYAML_FLAG_POINTER, handler_settings_t, doc_root, 0, CYAML_UNLIMITED),
    CYAML_FIELD_STRING_PTR("Default_Path", CYAML_FLAG_POINTER, handler_settings_t, default_path, 0, CYAML_UNLIMITED),
    CYAML_FIELD_BOOL("Keep_Alive", CYAML_FLAG_DEFAULT, handler_settings_t, keep_alive),
};

static const cyaml_schema_value_t schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, network_settings_t, ns_fields_schema),
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, handler_settings_t, hs_fields_schema),
};
//End CYAML schema settings and format

static hashTable_t* init_hashtable(network_settings_t* ns, handler_settings_t* hs) {
    hashTable_t* ht = create_table(HT_SIZE);
    
    insert(ht, "doc_root", hs->doc_root);
    insert(ht, "default_path", hs->default_path);
    insert(ht, "keep_alive", hs->keep_alive);
    insert(ht, "port_number", ns->port_number);
    insert(ht, "ipv4_address", ns->ipv4_address);
    insert(ht, "backlog", ns->backlog);
    insert(ht, "max_events", ns->max_events);

    return ht;
}

static hashTable_t* load_yaml(network_settings_t* ns, handler_settings_t* hs, char* filepath) {
    const cyaml_config_t config = {
        .log_fn = cyaml_log,
        .mem_fn = cyaml_mem,
        .log_level = CYAML_LOG_WARNING,
    };

    cyaml_err_t err = cyaml_load_file(filepath, &config, &schema, (void **)&ns, NULL);

    if(err != CYAML_OK) {perror("Error with CYAML: \n"); exit(EXIT_FAILURE);};

    hashTable_t* htable = init_hashtable(ns, hs);

    err = cyaml_free(&config, &schema, ns, 0);

    if(err != CYAML_OK) {perror("Error with CYAML: \n"); exit(EXIT_FAILURE);};

    free(ns);
    free(hs);

    return htable;
}

hashTable_t* settings(void) {
    network_settings_t* ns_settings = (network_settings_t*)malloc(sizeof(network_settings_t));
    handler_settings_t* hs_settings = (handler_settings_t*)malloc(sizeof(handler_settings_t));

    char* filepath;

    hashTable_t* hs = load_yaml(ns_settings, hs_settings, filepath);

    return hs;
}

void* get_setting() {

}