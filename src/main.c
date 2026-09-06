#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

#include "plugin_interface.h"
#include "plugin_manager.h"
#include "utils.h"
#include "types.h"


int main(int argn, char **argv){
  if(argn > 1) plugin_manager_set_plugins_path(argv[1]);
  PluginList p_list = PLUGIN_LIST_INIT;
  plugin_manager_get_plugins(&p_list);
  plugin_manager_load_all(&p_list);

  plugin_manager_unload_all(&p_list);
  plugin_list_free(&p_list);
  return 0;
}
