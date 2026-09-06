#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <dirent.h>

const char *plugin_path = "./plugin";

void printf_info(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs("[INFO]: ", stdout);
    vprintf(format, args);
  va_end(args);
}

void printf_error(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs("[ERROR]: ", stdout);
    vprintf(format, args);
  va_end(args);
}

typedef struct vector_dirent{
  size_t number;
  struct dirent **items;
} vector_dirent;

#define VECTOR_DIRENT_INIT {0, NULL}

void vector_dirent_free(vector_dirent *v){
  if(NULL == v) return;
  for(size_t i = 0; i < v->number; i++){
    free(v->items[i]);
  }
  free(v->items);
  v->items = NULL;
  v->number = 0;
}

void vector_dirent_append(vector_dirent *v, struct dirent *d){
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
    vector_dirent_append(v, current_item);
  }
  printf_info("Find %zu plugins in plugin folder!\n", v->number);
  for(size_t i = 0; i < v->number; i++){
    printf_info("[%d]%s \n", v->items[i]->d_type, v->items[i]->d_name);
  }
  printf("\n");

  closedir(plugin_dir);
}

// int main(int argv, char **argc){
int main(){
  vector_dirent v_dirent = VECTOR_DIRENT_INIT;
  init_plugin(&v_dirent);

  

  vector_dirent_free(&v_dirent);
  return 0;
}
