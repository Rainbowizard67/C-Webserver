#ifndef NETDATA_H
#define NETDATA_H

#include <cyaml/cyaml.h>
#include "hashTable.h"
#include "project_headers.h"

#define EXIT_MENU -1
#define NEUTRAL 0
#define INTERFACE_DATA 1
#define SET_HOST_IP 2

char* settings_menu();

#endif