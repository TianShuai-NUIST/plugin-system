#ifndef PLUGIN_VECTOR_H
#define PLUGIN_VECTOR_H

#include <unistd.h>

typedef struct vector_dirent{
  size_t number;
  struct dirent **items;
} vector_dirent;

#define VECTOR_DIRENT_INIT {0, NULL}

void vector_dirent_free(vector_dirent *v);
void vector_dirent_append(vector_dirent *v, struct dirent *d);

#endif
