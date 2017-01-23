/*
 * littletalk.c
 * 
 * muyunlei@gmail.com
 *
 *
 */

#include "littletalk.h"

int server()
{
	struct	sockaddr_in servaddr, cliaddr;
	int	listenfd, epfd;
	struct	epoll_event event, *events;
	int	nret;
	int	exit_flag = 0;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(LISTENPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd==-1){
		perror("socket err");
		exit(-1);
	}

	nret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(nret==-1){
		perror("bind err");
		exit(-1);
	}

	nret = setSocketNonblock(listenfd);
	if(nret==-1){
		perror("setSocketNonblock err");
		exit(-1);
	}

	epfd = epoll_create(MAXEPFDNUM);
	if(epfd==-1){
		perror("epoll_create err");
		exit(-1);
	}

	epdata *epd = malloc(sizeof(epdata));
	epd->fd = listenfd;
	event.data.ptr = epd;
	event.events = EPOLLIN | EPOLLERR;
	nret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
	if(nret==-1){
		perror("epoll_ctl err");
		exit(-1);
	}

	events = calloc(MAXEVENT, sizeof(event));

	while(!exit_flag){
		int eventno,i;
		eventno = epoll_wait(epfd, events, MAXEVENT, 1000);
		if(eventno==-1){
			perror("epoll_wait err");
			exit(-1);
		}
		for(i=0;i<eventno;++i){
			if((events[i].events&EPOLLERR)||
			    (events[i].events&EPOLLHUP)||
			    (!(events[i].events&EPOLLIN))){
				printf("epoll err\n");
				continue;
			}
		}
	}
	end:
		free(epd);
		exit(exit_flag);
		return 0;
}

int main(int argc, char **argv)
{
	return 0;
}
