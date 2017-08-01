#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SERV_TCP_PORT 7500

int main(int argc, char* argv[])
{
	int sockfd, newsockfd, clilen;
	int size;
	int pid, count=0;
	int val_set;
	
	char buff[30];
	
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
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	
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
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		
		count++;
		
		printf("%dth Client Enter\n",count);
		
		if(newsockfd < 0)
		{
			puts("Server : accept error!");
			exit(-1);
		}
	
	
		pid = fork();
		if(pid<0)
		{
			puts("fork : ERR");
			exit(-1);
		}
		
		if(pid==0)
		{
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
				printf("Child : Reading newsockfd from Client = %d \n",size);
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
		
			exit(0);			
		}	
	}
	close(sockfd);
	
	return 0;
	
}