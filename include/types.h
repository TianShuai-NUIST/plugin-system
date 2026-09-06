#ifndef TYPES_H
#define TYPES_H

#include <unistd.h>

#include "plugin_interface.h"

typedef struct Plugin{
  void *handle;
  char path[256];
  PluginInterface *interface;
} Plugin;

typedef struct Plugin_list{
  size_t number;
  struct dirent **items;
} Plugin_list;

#define PLUGIN_LIST_INIT {0, NULL}
void plugin_list_free(plugin_list *v);
void plugin_list_append(plugin_list *v, struct dirent *d);

#endif
