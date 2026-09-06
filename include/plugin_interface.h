#ifndef PLGUIN_INTERFACE_H
#define PLGUIN_INTERFACE_H

typedef struct {
	const char* plugin_name;
	const char* display_name;
	const char* auther;
	unsigned int version;

	int (*init)(void);
	void (*execute)(void);
	void (*cleanup)(void);

} PluginInterface;

#endif
