#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "types.h"

void plugin_manager_set_plugins_path(const char* path);
void plugin_manager_load_all(PluginList *p);
void plugin_manager_unload_all(PluginList *p);
void plugin_manager_execute_all(PluginList *p);

#endif
