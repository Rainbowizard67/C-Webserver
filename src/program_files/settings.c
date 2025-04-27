#include "../headers/settings.h"

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

static const cyaml_schema_field_t ns_fields_schema[] = {
    CYAML_FIELD_UINT_PTR("Port_Number", CYAML_FLAG_DEFAULT, network_settings_t, port_number),
    CYAML_FIELD_STRING_PTR("IPv4_Address", CYAML_FLAG_POINTER, network_settings_t, ipv4_address, 0, CYAML_UNLIMITED),
    CYAML_FIELD_UINT_PTR("Backlog", CYAML_FLAG_POINTER, network_settings_t, backlog),
    CYAML_FIELD_UINT_PTR("Max_Events", CYAML_FLAG_POINTER, network_settings_t, max_events),
    CYAML_FIELD_END
};

static const cyaml_schema_value_t ns_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, network_settings_t, ns_fields_schema),
};

static const cyaml_config_t config = {
    
};


static hashTable_t* construct_ht(int size) {
    hashTable_t * ht = create_table(size);

}

void parse_yaml() {

}

void init_settings() {

}
