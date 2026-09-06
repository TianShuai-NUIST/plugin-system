#include "utils.h"

#include <stdarg.h>
#include <stdio.h>

void printf_info(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs("[INFO]: ", stdout);
    vprintf(format, args);
  va_end(args);
}

void printf_error(const char *format, ...){
  va_list args;
  va_start(args, format);
    fputs("[ERROR]: ", stdout);
    vprintf(format, args);
  va_end(args);
}
