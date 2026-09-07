#ifndef UTILS_H
#define UTILS_H

#ifdef DEBUG
#define DEBUG_LOG(x) \
do{                  \
x;                   \
}while(0);
#else
#endif

void printf_info(const char *format, ...);
void printf_warning(const char *format, ...);
void printf_error(const char *format, ...);

#endif
