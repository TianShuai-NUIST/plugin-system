#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "types.h"

#define PLUGIN_CHECK_HANDLE(x, list)\
if((list)->plugins[(x)].handle == NULL){\
  printf_error("plugin \"%s\" with \"NULL\" of handle!\n", (list)->plugins[(x)].filename);\
  continue;\
}

#define PLUGIN_CHECK_IFACE(x, list, member)\
if((list)->plugins[(x)].iface.member== NULL){\
  printf_warning("cant %s \"%s\", find \"NULL\" with functions pointer: %s\n", #member, (list)->plugins[(x)].filename, strerror(errno));\
  continue;\
}

void plugin_manager_set_plugins_path(const char* path);
void plugin_manager_load_all(PluginList *p);
void plugin_manager_unload_all(PluginList *p);
void plugin_manager_execute_all(PluginList *p);

#endif
