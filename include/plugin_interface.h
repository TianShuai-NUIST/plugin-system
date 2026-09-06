#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#define PLUGIN_API_VERSION 1

typedef struct PluginInterface{
	const char* name;
	const char* auther;
	unsigned int version;

	int (*initialize)(void);
	void (*execute)(void);
	void (*cleanup)(void);

} PluginInterface;

#endif
