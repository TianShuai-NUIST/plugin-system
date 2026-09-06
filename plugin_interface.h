#ifndef PLGUIN_INTERFACE_H
#define PLGUIN_INTERFACE_H

typedef struct {
	const char* name;
	const char* version;

	int (*init)(void);
	void (*execute)(void);
	void (*cleanup)(void);

} PluginInterface;

#endif
