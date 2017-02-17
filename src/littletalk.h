/*
 * a small chat room server
 *
 * littletalk.h
 *
 * muyunlei@gmail.com
 */

#ifndef _LITTLETALK_H
#define _LITTLETALK_H

/* std lib */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


/* net lib */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/epoll.h>

/* linux kernal data st */
#include "list.h"
#include "rbtree.h"

/* LIMIT MACRO */
#define LISTENPORT 20124

#define HEADLEN 4
#define MAXBUFLEN 1024

#define MAXEPFDNUM 1024
#define MAXEVENT 128

typedef struct{
	char inbuf[MAXBUFLEN];
	char outbuf[MAXBUFLEN];

	int fd;

}epdata;

int set_socket_nonblock(int);
int create_and_bind(const char *);


#endif
