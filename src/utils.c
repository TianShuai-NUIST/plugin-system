#include "utils.h"
#define NONE   "\033[0m"
#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define ORANGE "\033[38;5;208m"

#include <stdarg.h>
#include <stdio.h>

void printf_info(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs("[INFO]: ", stdout);
    vprintf(format, args);
  va_end(args);
}

void printf_warning(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs(ORANGE"[WARNING]: "NONE, stdout);
    vprintf(format, args);
  va_end(args);
}

void printf_error(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs(RED"[ERROR]: "NONE, stdout);
    vfprintf(stdout, format, args);
  va_end(args);
}
