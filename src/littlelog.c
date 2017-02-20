/* littlelog.c */

#include "littlelog.h"

char g_logfile[ MAXLEN_FILENAME ] = "";
int g_log_level = LOG_INFO;

const char log_level_map[][6] = {"DEBUG","INFO","WARN","ERROR","FATAL"};

void set_log_file(const char *fmt, ...)
{
	va_list valist;
	va_start(valist, fmt);
	vsnprintf(g_logfile, sizeof(g_logfile)-1, fmt, valist);
	va_end(valist);

	return;
}

void set_log_level(const int log_level)
{
	g_log_level = log_level;
	return;
}

void little_log_(const int log_level,\
		const char *c_filename,\
		const long c_fileline,\
		const char *fmt, ...)
{
	struct timeval tv;
	struct tm stime;
	char log_buf[4096+1] = {0};
	int log_buf_len = 0;
	va_list valist;
	va_start(valist, fmt);

	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &stime);

	log_buf_len = strftime(log_buf, sizeof(log_buf), "%Y-%m-%d %H:%M:%S", &stime); // datetime
	log_buf_len += snprintf(log_buf+log_buf_len, sizeof(log_buf)-log_buf_len-1, ".%06ld", (long)tv.tv_usec); // timestrap
	log_buf_len += snprintf(log_buf+log_buf_len, sizeof(log_buf)-log_buf_len-1, "| %s ", log_level_map[log_level]); // log level
	log_buf_len += snprintf(log_buf+log_buf_len, sizeof(log_buf)-log_buf_len-1, "| %ld:%s:%ld |", PROCESSID, c_filename, c_fileline); // pid and file
	log_buf_len += vsnprintf(log_buf+log_buf_len, sizeof(log_buf)-log_buf_len-1, fmt, valist); // content

	va_end(valist);

	if(g_log_level>=log_level){
		if(g_logfile[0]=='\0'){
			fprintf(stdout, "%s\n", log_buf);
		}else{
			FILE *fd;
			fd = fopen(g_logfile, "a");
			if(fd==NULL){
				perror("fopen err");
				exit(-1);
			}

			fprintf(fd, "%s\n", log_buf);

			fclose(fd);
		}
	}

	return;
}

