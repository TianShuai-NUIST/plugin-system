# plugin-system

C 写的运行时插件加载器。启动时扫目录，`dlopen` 每个动态库，校验版本号后调用。

## 怎么跑

```bash
make
make test          # 类型层单测
./build/main       # 默认扫 ./plugin
```

依赖 gcc、make，和 Linux 的 `dlfcn.h`。

## 实现

**接口约定**：每个插件导出同名的 `plugin_interface` 结构体，里面是版本号加一组函数指针（`initialize` / `execute` / `cleanup` / `name`）。主程序 `dlsym` 拿到它，先比版本号，不匹配直接 `dlclose`。

**句柄和接口分开存**：`PluginList` 是自己写的动态数组（`types.c`），元素是 `{ void *handle, plugin_interface *iface }`。`dlclose` 要的是 `dlopen` 返回的原始句柄，调用只要函数指针。

**分阶段**：`load_all` → `init_all` → `execute_all` → `cleanup_all` → `unload_all`。不 load 完立刻 init，是因为某个插件 `initialize` 失败时，前面已经初始化过的还能正常 `cleanup`。

## 已知限制

- 只按 `.plugin` 后缀筛文件，不递归子目录
- 没有热卸载，运行期间换不掉已加载的插件
- 插件之间不能互相调用
- 没有沙箱，插件段错误会带崩整个进程
