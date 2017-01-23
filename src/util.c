/*
 * util.c
 *
 */

#include "littletalk.c"

#include <fcntl.h>

int setSocketNonblock(sfd)
{
	int flags, ret;
	flags = fcntl(sfd, F_GETFL, 0);
	if(flags==-1){
		perror("fcntl get fd flags err!");
		return -1
	}

	flags |= O_NONBLOCK;
	ret = fcntl(sfd, F_SETFL, flags);
	if(ret==-1){
		perror("fcntl set fd flags err!");
		return -1;
	}
	return 0;
}


