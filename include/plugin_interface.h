/*
 * 插件必须导出全局plugin_interface, 设置对应的所有字段.
 * version 必须与如下宏对应
 * #define PLUGIN_API_VERSION 1
 * */


#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#define PLUGIN_API_VERSION 1

typedef struct PluginInterface{
	const char* name;
	const char* author;
	unsigned int version;

	int (*initialize)(void);
	void (*execute)(void);
	void (*cleanup)(void);

} PluginInterface;

#endif
