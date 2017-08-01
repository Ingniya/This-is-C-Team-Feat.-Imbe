#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>


#define SERV_TCP_PORT 7500
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	
	char buff[BUFSIZE];
	
	struct sockaddr_in serv_addr;
	
	pthread_t thread_t1, thread_t2;
	

	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons((short)atoi(argv[2]));;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		puts("Client : Can't open stream socket.");
		exit(-1);
	}

	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		puts("Client : Can't connect the server.");
		exit(-1);
	}

	while(1)
	{
		printf("Input(quit) :::: ");
		fgets(buff,BUFSIZE,stdin);
		
		if(!strncmp(buff,"quit",4))
			break;
		
		
		if(pthread_create(&thread_t1, NULL, perform, (void *)&arg_th) < 0)
		{
			perror("Thread Create Error!!");
			close(sockfd);
			exit(1);
			
		}
		
		if(pthread_create(&thread_t2, NULL, perform, (void *)&arg_th) < 0)
		{
			perror("Thread Create Error!!");
			close(sockfd);
			exit(1);
		}
		
		
		if(write(sockfd, buff, 20) < 20)
		{
			puts("Client : writen error");
			exit(-1);
		}
		
		
		if(read(sockfd, buff, 1024) < 20)
		{
			puts("Client : readn error!");
			exit(1);
		}
		
		
		printf("Client : Received String = %s \n",buff);
	}
	
	

	close(sockfd);

	return 0;
}

