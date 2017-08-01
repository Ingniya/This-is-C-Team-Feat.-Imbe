#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>

#define SERV_TCP_PORT 8000

int main(int argc, char* argv[])
{
	int sockfd, newsockfd, clilen;
	int size, val_get, val_set, len_r, len_t, len_l;
	
	char buff[30];
	
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	struct timeval time_get;
	struct timeval time_set;
	
	len_t = sizeof(struct timeval);
	len_r = sizeof(val_get);
	len_l = sizeof(struct linger);
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		puts("Server : Can't open Stream Socket.");
		exit(1);
	}
	
	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	
	val_set = 1;
	val_get = 0;
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val_set, sizeof(val_set));
	getsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val_get, &len_r);
	
	printf("after set reuse addr val : %d\n",val_get);
	
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		puts("Server : Can't bind Local Address.");
		exit(1);
	}
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	
	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		
		if(newsockfd < 0)
		{
			puts("Server : accept error!");
			exit(1);
		}
		
		memset(&time_set, 0, sizeof(time_set));
		time_set.tv_sec = 30;
		
		setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, &time_set, sizeof(time_set));
		getsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, &time_get, &len_t);
		
		printf("after set time out %d %d \n", time_get.tv_sec, time_get.tv_usec);
		
		if((size = read(newsockfd, buff, 20)) <= 0)
		{
			puts("Server : readn error!");
			exit(1);
		}
		
		printf("Reading Newsockfd From Client = %d\n", size);
		printf("Server : Received String = %s\n",buff);
		
		close(newsockfd);
	}
	
	close(sockfd);
	
	return 0;
	
}