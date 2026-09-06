#include "plugin_manager.h"

static const char *plugin_manager_plugins_path = "./plugin";

void plugin_manager_set_plugins_path(const char* path){
  plugin_manager_plugins_path = path;
}

static void plugin_manager_get_plugins(PluginList *v){
  // print current path
  char current_path[PATH_MAX];
  getcwd(current_path, PATH_MAX);
  printf_info("Current path is %s\n", current_path);

  // open plugin dir
  DIR* plugin_dir = opendir(plugin_manager_plugins_path);
  if(plugin_dir == NULL){
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
    exit(1);
  }

  // get plugin name
  struct dirent *current_item;
  while((current_item = readdir(plugin_dir))){
    if(!strncmp(".", current_item->d_name, 1)) continue;
    if(current_item->d_type != DT_REG) continue;
    Plugin p = PLUGIN_INIT;
    strncpy(p.filename, current_item->d_name, sizeof(p.filename) - 1);
    // 如果超出长度, strnpy不保证结尾\0, 所以我们手动加上
    p.filename[sizeof(p.filename) - 1] = '\0';
    plugin_list_append(v, &p);
  }
  printf_info("Find %zu plugins in plugin folder!\n", v->number);
  closedir(plugin_dir);
}

void plugin_manager_load_all(PluginList *p){
  plugin_manager_get_plugins(p);
  for(size_t i = 0; i < p->number; i++){
    char path[PATH_MAX];
    int n = snprintf(path, sizeof(path), "%s/%s", plugin_manager_plugins_path, p->plugins[i].filename);
    if(n < 0 || (size_t)n >= sizeof(path)){
      printf_error("path too long for plugin \"%s\", skip\n", p->plugins[i].filename);
      continue;
    }
    dlerror();
    p->plugins[i].handle = dlopen(path, RTLD_LAZY);
    if(NULL == p->plugins[i].handle){
      printf_error("Cant load plugin \"%s\": %s\n", p->plugins[i].filename, dlerror());
      continue;
    } else {
      printf_info("load plugin \"%s\" Success!\n", p->plugins[i].filename);
    }
    dlerror();
    PluginInterface *iface = (PluginInterface *)dlsym(p->plugins[i].handle, "plugin_interface");
    if(iface == NULL){
      printf_error("Cant load <plugin_interface> in plugin \"%s\": %s\n", p->plugins[i].filename, dlerror());
      dlclose(p->plugins[i].handle);
      p->plugins[i].handle = NULL;
      continue;
    }

    if(iface->version != PLUGIN_API_VERSION){
      printf_error("Cant load plugin \"%s\": Version cant match!\n", p->plugins[i].filename);
      dlclose(p->plugins[i].handle);
      p->plugins[i].handle = NULL;
      continue;
    }
    p->plugins[i].iface = *iface;
    if(p->plugins[i].iface.initialize() != 0){
      printf_error("Cant init plugin \"%s\"!\n", p->plugins[i].filename);
      dlclose(p->plugins[i].handle);
      p->plugins[i].handle = NULL;
      continue;
    }
  }
}

void plugin_manager_unload_all(PluginList *p){
  for(size_t i = 0; i < p->number; i++){
    if(p->plugins[i].handle == NULL) continue;

    p->plugins[i].iface.cleanup();

    if(dlclose(p->plugins[i].handle) == 0){
      printf_info("unload plugin \"%s\" Success!\n", p->plugins[i].filename);
      p->plugins[i].handle = NULL;
    } else {
      printf_error("Cant unload plugin \"%s\": %s\n", p->plugins[i].filename, dlerror());
      continue;
    }
  }
}

void plugin_manager_execute_all(PluginList *p){
  for(size_t i = 0; i < p->number; i++){
    if(p->plugins[i].handle == NULL) continue;
    if(p->plugins[i].iface.execute == NULL) continue;
    p->plugins[i].iface.execute();
  }
}
