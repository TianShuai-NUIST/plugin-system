#ifndef TYPES_H
#define TYPES_H

#include <limits.h>
#include <stddef.h>

#include "plugin_interface.h"
#include "utils.h"

typedef struct Plugin{
  void *handle;
  char filename[NAME_MAX + 1];
  PluginInterface iface;
} Plugin;

#define PLUGIN_INIT {                 \
  .handle = NULL,                     \
    .filename = "",                   \
    .iface = (PluginInterface){       \
      .name = "",                     \
      .auther = "",                   \
      .version = 0,                   \
      \
      .initialize = NULL,             \
      .execute = NULL,                \
      .cleanup = NULL                 \
    }                                 \
}                                     \

typedef struct PluginList{
  size_t len;
  // struct dirent **items;
  Plugin *plugins;
} PluginList;

#define PLUGIN_LIST_INIT {0, NULL}
void plugin_list_free(PluginList *v);
void plugin_list_append(PluginList *v, const Plugin *p);
#define FOR_EACH(x, list)\
for(size_t (x) = 0; (x) < list->len; (x)++)

#endif
