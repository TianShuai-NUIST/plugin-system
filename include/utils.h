#ifndef UTILS_H
#define UTILS_H

#define DEBUG_LOG(x)/
#ifdef DEGUG/
do{/
  x;/
} while(0);/
#endif/

void printf_info(const char *format, ...);
void printf_warning(const char *format, ...);
void printf_error(const char *format, ...);

#endif
