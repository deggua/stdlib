#pragma once

#include <stdio.h>

#define ANSI_START "\x1B["
#define ANSI_END   "m"

#define ANSI_FG_RED     ";31"
#define ANSI_FG_YELLOW  ";33"
#define ANSI_FG_BLUE    ";34"
#define ANSI_FG_MAGENTA ";35"

#define ANSI_BOLD  "1"
#define ANSI_FAINT "2"
#define ANSI_BLINK "5"

#define ANSI_RESET_ALL   "\x1B[0m"
#define ANSI(style, str) ANSI_START style ANSI_END str ANSI_RESET_ALL

#define LOCATION_STYLE ANSI_FAINT
#define ERROR_STYLE    ANSI_BOLD ANSI_FG_RED
#define WARNING_STYLE  ANSI_BOLD ANSI_FG_YELLOW
#define INFO_STYLE     ANSI_BOLD ANSI_FG_BLUE
#define DEBUG_STYLE    ANSI_BOLD ANSI_FG_MAGENTA

#if !defined(DISABLE_LOGGING)
#    define _LOG_INTERNAL(fd, prefix, msg, ...) \
        fprintf(fd, prefix ANSI(LOCATION_STYLE, "| %30s:%-4d | ") msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#    define _LOG_INTERNAL(prefix, msg, ...)
#endif

#define LOG_ERROR(msg, ...)   _LOG_INTERNAL(stdout, ANSI(ERROR_STYLE,   " ERROR   "), msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) _LOG_INTERNAL(stdout, ANSI(WARNING_STYLE, " WARNING "), msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...)    _LOG_INTERNAL(stdout, ANSI(INFO_STYLE,    " INFO    "), msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...)   _LOG_INTERNAL(stdout, ANSI(DEBUG_STYLE,   " DEBUG   "), msg, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...)   _LOG_INTERNAL(stderr, ANSI(ERROR_STYLE,   " FATAL   "), msg, ##__VA_ARGS__)
