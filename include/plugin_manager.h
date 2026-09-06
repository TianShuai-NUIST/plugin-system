#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "types.h"
#include "utils.h"


void plugin_manager_set_plugins_path(const char* path);
void plugin_manager_get_plugins(PluginList *v);
void plugin_manager_load_all(PluginList *p);
void plugin_manager_unload_all(PluginList *p);

#endif
