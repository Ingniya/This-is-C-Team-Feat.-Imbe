#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define SERV_TCP_PORT 7000

struct arg_thread
{
	int sockfd_thread;
	int clilen_thread;
	
	struct sockaddr_in cli_addr_thread;
}arg_th;

void* perform(void *);

int main(void){
	int sockfd, clilen;
	
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	
	pthread_t thread_t;
	

	if((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0){
		puts("Server : Can't open Stream Socket.");
		exit(1);
	}
	else
	{
		puts("Server : Opening the Stream Socket is success!!");
	}

	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		puts("Server : Can't bind Local Address.");
		exit(-1);
	}


	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	arg_th.sockfd_thread = sockfd;
	arg_th.clilen_thread = clilen;
	arg_th.cli_addr_thread = cli_addr;

	if(pthread_create(&thread_t, 0, perform, (void *)&arg_th) < 0)
	{
		perror("Thread Create Error!!");
		close(sockfd);
		exit(1);
	}
	pthread_join(thread_t, NULL);
	

	close(sockfd);
	
	return 0;
}

void* perform(void *arg)
{
	int size;
	char buff[30];
	
	int newsockfd;
	int sockfd = ((struct arg_thread*)arg)->sockfd_thread;
	int clilen = ((struct arg_thread*)arg)->clilen_thread;
	struct sockaddr_in cli_addr = ((struct arg_thread*)arg)->cli_addr_thread;
	
	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
			

		if(newsockfd < 0)
		{
			puts("Server : accept error!");
			exit(-1);
		}

		

		if((size = read(newsockfd, buff, 20)) <= 0)
		{
			puts("Server : readn error!");
			exit(-1);
		}

		printf("reading newsockfd from Client = %d\n", size);
		printf("Server : Received String = %s \n", buff);
		close(newsockfd);
	}
}			
