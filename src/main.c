#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <dirent.h>

#include "plugin_interface.h"
#include "utils.h"
#include "plugin_vector.h"

const char *plugin_path = "./plugin";

void init_plugin(vector_dirent *v){
  char current_path[256];
  getcwd(current_path, 256);
  printf_info("Current path is %s\n", current_path);

  DIR* plugin_dir = opendir(plugin_path);
  if(plugin_dir == NULL){
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
    exit(1);
  }

  struct dirent *current_item;
  while((current_item = readdir(plugin_dir))){
    if(!strncmp(".", current_item->d_name, 1)) continue;
    if(current_item->d_type != DT_REG) continue;
    vector_dirent_append(v, current_item);
  }
  printf_info("Find %zu plugins in plugin folder!\n", v->number);
  for(size_t i = 0; i < v->number; i++){
    printf_info("[%d]%s \n", v->items[i]->d_type, v->items[i]->d_name);
  }
  printf("\n");

  closedir(plugin_dir);
}

int main(int argn, char **argv){
  if(argn > 1) plugin_path = argv[1];
  vector_dirent v_dirent = VECTOR_DIRENT_INIT;
  init_plugin(&v_dirent);

  for(size_t i = 0; i < v_dirent.number; i++){
  }

  vector_dirent_free(&v_dirent);
  return 0;
}
