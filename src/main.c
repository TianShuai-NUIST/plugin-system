#include "plugin_manager.h"
#include "types.h"
#include "utils.h"

int main(int argn, char **argv){
  if(argn > 1) plugin_manager_set_plugins_path(argv[1]);
  PluginList p_list = PLUGIN_LIST_INIT;
  plugin_manager_load_all(&p_list);

  plugin_manager_execute_all(&p_list);

  plugin_manager_unload_all(&p_list);
  plugin_list_free(&p_list);
  return 0;
}
