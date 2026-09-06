#include "types.h"

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void plugin_list_free(plugin_list *v){
  if(NULL == v) return;
  for(size_t i = 0; i < v->number; i++){
    free(v->items[i]);
  }
  free(v->items);
  v->items = NULL;
  v->number = 0;
}

void plugin_list_append(plugin_list *v, struct dirent *d){
  struct dirent **new_items = (struct dirent**)malloc(sizeof(struct dirent*) * (v->number + 1));
  if(v->items != NULL){
    memcpy(new_items, v->items, v->number * sizeof(struct dirent *));
    free(v->items);
  }

  struct dirent *copy = (struct dirent *)malloc(sizeof(struct dirent));
  *copy = *d;
  new_items[v->number] = copy;

  v->items = new_items;
  v->number++;
}
