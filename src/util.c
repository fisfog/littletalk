/*
 * util.c
 *
 */

#include "littletalk.h"

#include <fcntl.h>

int set_socket_nonblock(int sfd)
{
	int flags, ret;
	flags = fcntl(sfd, F_GETFL, 0);
	if(flags==-1){
		little_log_error(__FILE__,__LINE__,"fcntl get fd flags err");
		return -1;
	}

	flags |= O_NONBLOCK;
	ret = fcntl(sfd, F_SETFL, flags);
	if(ret==-1){
		little_log_error(__FILE__,__LINE__,"fcntl set fd flags err");
		return -1;
	}
	return 0;
}

int create_and_bind(const char *port)
{
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	int s,sfd;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // Tcp socket
	hints.ai_flags = AI_PASSIVE; 
	
	s = getaddrinfo(NULL, port, &hints, &result);
	if(s){
		little_log_error(__FILE__,__LINE__,"getaddrinfo error[%s]", gai_strerror(s));
		return -1;
	}
	
	for(rp = result; rp!=NULL; rp=rp->ai_next){
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if(sfd == -1)
			continue;
		s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if(s==0){
			// bind successful
			break;
		}
		close(sfd);
	}
	
	if(rp==NULL){
		little_log_error(__FILE__,__LINE__,"could not bind");
		return -1;
	}

	freeaddrinfo(result);
	return sfd;

}
