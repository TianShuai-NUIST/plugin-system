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
  if(NULL == v || NULL == p) {
    printf_error("argument is NULL!\n");
    return;
  }

  if(v->len == v->capacity){
    size_t new_capacity = (v->capacity == 0) ? 4 : v->capacity * 2;
    Plugin *temp = realloc(v->plugins, new_capacity * sizeof(Plugin));
    if(temp == NULL){
      printf_error("Cant append item (%s): %s\n", p->filename, strerror(errno));
      // TODO: 错误后处理
      return;
    }
    v->plugins = temp;
    v->capacity = new_capacity;
  }
  v->plugins[v->len++] = *p;
}
