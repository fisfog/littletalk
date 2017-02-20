/*
 * littletalk.c
 * 
 * muyunlei@gmail.com * *
 */

#include "littletalk.h"


int server()
{
	struct	sockaddr_in servaddr, cliaddr;
	int	listenfd, epfd;
	struct	epoll_event event, *events;
	int	nret;
	int	exit_flag = 0;


	listenfd = create_and_bind(LISTENPORT);
	if(listenfd==-1){
		little_log_error(__FILE__, __LINE__, "create and bind listen fd error");
		return -1;
	}

	nret = set_socket_nonblock(listenfd);
	if(nret==-1){
		little_log_error(__FILE__, __LINE__, "set socket nonblock error");
		return -1;
	}

	nret = listen(listenfd, SOMAXCONN);
	if(nret==-1){
		little_log_error(__FILE__, __LINE__, "listen port[%s] error, errno[%d]", LISTENPORT, errno);
		return -1;
	}

	epfd = epoll_create(MAXEPFDNUM);
	if(epfd==-1){
		little_log_error(__FILE__, __LINE__, "epoll create error, errno[%d]", errno);
		return -1;
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
			exit_flag = -1;
			goto end;
		}
		for(i=0;i<eventno;++i){
			if((events[i].events&EPOLLERR)|| \
					(events[i].events&EPOLLHUP)){
				printf("epoll err\n");
				continue;
				//			}else if(events[i].data.ptr->fd==listenfd){

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
	set_log_file("./log/littletalk.log");
	set_log_level(LITTLETALK_LOG_LEVEL);

	little_log_debug(__FILE__,__LINE__,"littlelog debug test");
	little_log_info(__FILE__,__LINE__,"littlelog info test");
	little_log_error(__FILE__,__LINE__,"littlelog error test");
	return 0;
}
