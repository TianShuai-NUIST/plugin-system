#include "types.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

void plugin_list_free(PluginList *v){
  if(NULL == v) return;
  free(v->plugins);
  v->plugins = NULL;
  v->len = 0;
}

void plugin_list_append(PluginList *v, const Plugin *p){
  Plugin *new_items = (Plugin *)malloc(sizeof(Plugin) * (v->len + 1));
  if(new_items == NULL){
    printf_error("Cant append item (%s): %s\n", p->filename, strerror(errno));
    return;
  }
  if(v->plugins != NULL){
    memcpy(new_items, v->plugins, v->len * sizeof(Plugin));
    free(v->plugins);
  }

  new_items[v->len] = *p;

  v->plugins = new_items;
  v->len++;
}
