/* littlelog.h
* light log lib for littletalk
* 
* muyunlei@gmail.com
*/

#ifndef _LITTLELOG_H
#define _LITTLELOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>

#define MAXLEN_FILENAME 256
#define PROCESSID (unsigned long)getpid()

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 3
#define LOG_FATAL 4

#define little_log_debug(filename, fileline, ...) \
	little_log_(LOG_DEBUG, filename, fileline, __VA_ARGS__)

#define little_log_info(filename, fileline, ...) \
	little_log_(LOG_INFO, filename, fileline, __VA_ARGS__)

#define little_log_warn(filename, fileline, ...) \
	little_log_(LOG_WARN, filename, fileline, __VA_ARGS__)

#define little_log_error(filename, fileline, ...) \
	little_log_(LOG_ERROR, filename, fileline, __VA_ARGS__)

#define little_log_fatal(filename, fileline, ...) \
	little_log_(LOG_FATAL, filename, fileline, __VA_ARGS__)

void little_log_(const int log_level, \
		const char *c_filename, \
		const long c_fileline, \
		const char *fmt, ...);

void set_log_file(const char *fmt, ...);
void set_log_level(int log_level);

#endif /* _LITTLELOG_H */
