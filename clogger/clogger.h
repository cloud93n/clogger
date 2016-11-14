

#ifndef HLOGGER_H
#define HLOGGER_H




#include <time.h>
#include <string.h>
#include <fstream>
#include <iostream>

// === auxiliar functions
static inline char *timenow();

//logging file
#define LOGFILE std::ofstream outfile;\
                outfile.open("LOGNAME.LOG", ios::out | ios::trunc);


//shorten file path
#define _FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__

#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define INFO_LEVEL      0x02
#define DEBUG_LEVEL     0x03

#ifndef LOG_LEVEL
#define LOG_LEVEL   DEBUG_LEVEL
#endif

//to prevent unexpected value for log_level
#ifdef LOG_LEVEL
#if LOG_LEVEL <0 || LOG_LEVEL>3
#define LOG_LEVEL DEBUG_LEVEL
#endif
#endif

//function to print expression and identifier
// use _()
#ifdef PRINT_VAR
#define _(x) std::cout << #x << std::endl; x
#else
#define _(x) x

#endif //log_level==debug_level

#define PRINTFUNCTION(format, ...)      fprintf(stderr, format, ##__VA_ARGS__)


#define LOG_FMT             "%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)   timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

#define NEWLINE     "\n"

#define ERROR_TAG   "ERROR"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG), ## __VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...)      PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG), ## __VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## __VA_ARGS__)
#else
#define LOG_ERROR(message, ...)
#endif

#if LOG_LEVEL >= NO_LOG
#define LOG_IF_ERROR(condition, message, ...) if (condition) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## __VA_ARGS__)
#else
#define LOG_IF_ERROR(condition, message, ...)
#endif

static inline char *timenow() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}



#endif