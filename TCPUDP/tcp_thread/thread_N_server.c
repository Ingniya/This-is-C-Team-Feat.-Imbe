#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>


struct arg_thread
{
	int newsockfd_thread;
	int count_thread;
	struct sockaddr_in serv_addr_thread;
}arg_th;

void* perform(void *);

int main(int argc, char* argv[])
{
	int sockfd, newsockfd, clilen;
	
	int count=0;
	int val_set;
	pthread_t thread_t;
	
	
	
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	
	
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		puts("Server : Can't open Stream Socket.");
		exit(-1);
	}
	
	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons((short)atoi(argv[1]));;
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val_set, sizeof(val_set));
	
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		puts("Server : Can't bind Local Address.");
		exit(-1);
	}
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	signal(SIGCHLD,SIG_IGN);
	
	while(1)
	{	
		#if 1
		if((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0)
		{
			puts("Server : accept error!");
			exit(-1);
		}
		#endif
		
		#if 0
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if(newsockfd<0)
		{
			puts("Server : accept error!");
			exit(-1);
		}
		#endif
		
		count++;
		
		printf("%dth Client Enter\n",count);
		
		arg_th.newsockfd_thread = newsockfd;
		arg_th.count_thread = count;
		arg_th.serv_addr_thread = serv_addr;
		
		if(pthread_create(&thread_t, NULL, perform, (void *)&arg_th) < 0)
		{
			perror("Thread Create Error!!");
			close(sockfd);
			exit(1);
		}
		
		
	}
	
	pthread_join(thread_t, NULL);
	
	close(sockfd);
	
	return 0;
	
}


void* perform(void *arg)
{
	char buff[30];
	int size;
	
	int newsockfd = ((struct arg_thread*)arg)->newsockfd_thread;
	int count = ((struct arg_thread*)arg)->count_thread;
	struct sockaddr_in serv_addr = ((struct arg_thread*)arg)->serv_addr_thread;
	
	
	while(1)
	{
		bzero(buff, sizeof(buff));
		//memset(buff,0,20);
		
		if((size = read(newsockfd, buff, 20)) <= 0)
		{
			puts("Server : readn error!");
			break;
		}
		
		printf("**%dth Client**\n",count);
		printf("Port : %d \n",ntohs(serv_addr.sin_port));
		printf("Server : Received String = %s \n",buff);

		if((size = write(newsockfd, buff, 20)) <= 0)
		{
			puts("Server : writen error!");
			break;
		}
	}
	
	
	close(newsockfd);

	printf("%dth Client go out\n",count);
	count--;

	return 0;
}
