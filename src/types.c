#include "types.h"

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void plugin_list_free(PluginList *v){
  if(NULL == v) return;
  free(v->plugins);
  v->plugins = NULL;
  v->number = 0;
}

void plugin_list_append(PluginList *v, const Plugin *p){
  Plugin *new_items = (Plugin *)malloc(sizeof(Plugin) * (v->number + 1));
  if(v->plugins != NULL){
    memcpy(new_items, v->plugins, v->number * sizeof(Plugin));
    free(v->plugins);
  }

  new_items[v->number] = *p;

  v->plugins = new_items;
  v->number++;
}
