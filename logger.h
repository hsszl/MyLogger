#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <io.h>
#include <direct.h>

#define TRACE 0
#define DEBUG 1
#define INFO 2
#define WARNING 3
#define ERROR 4
#define EXCEPTION 5

char *name;
int level;
void init(char *name_, int level_) {
    name = name_;
    level = level_;
}

char *level2char(int level_) {
    if (level_ == TRACE) {return "TRACE";}
    else if (level_ == DEBUG) {return "DEBUG";}
    else if (level_ == INFO) {return "INFO";}
    else if (level_ == WARNING) {return "WARNING";}
    else if (level_ == ERROR) {return "ERROR";}
    else if (level_ == EXCEPTION) {return "EXCEPTION";}
}

void logger(int error_level, const char *format) {
    if (_access("log", 0) == -1) {_mkdir("log");}
    va_list args;
    FILE *fp=NULL;
    char time_str[32];
    char file_name[256];

    time_t time_log = time(NULL);

    strftime(file_name, sizeof(file_name), "log\\%Y-%m-%d %H-%M-%S_log.log", localtime(&time_log));

    if((fp=fopen(file_name,"a+")) != NULL) {
        char output[256];
        strftime(time_str,sizeof(time_str),"%Y-%m-%d %H:%M:%S",localtime(&time_log));
        sprintf(output, "[%s] [%s] [%s]: %s\n", time_str, level2char(error_level), name, format);
        fprintf(fp, output);
        if (error_level >= level) {printf(output);}
        fclose(fp);
    }
}

void trace(const char *format, ...) {logger(TRACE, format);}
void debug(const char *format, ...) {logger(DEBUG, format);}
void info(const char *format, ...) {logger(INFO, format);}
void warning(const char *format, ...) {logger(WARNING, format);}
void error(const char *format, ...) {logger(ERROR, format);}
void exception(const char *format, ...) {logger(EXCEPTION, format);}
