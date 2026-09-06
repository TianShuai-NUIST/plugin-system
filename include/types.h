#ifndef TYPES_H
#define TYPES_H

#include <unistd.h>
#include <limits.h>

#include "plugin_interface.h"

typedef struct Plugin{
  void *handle;
  char filename[NAME_MAX + 1];
  PluginInterface interface;
} Plugin;

#define PLUGIN_INIT {                 \
  .handle = NULL,                     \
    .filename = "",                   \
    .interface = (PluginInterface){   \
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
  size_t number;
  // struct dirent **items;
  Plugin *plugins;
} PluginList;

#define PLUGIN_LIST_INIT {0, NULL}
void plugin_list_free(PluginList *v);
void plugin_list_append(PluginList *v, const Plugin *p);

#endif
