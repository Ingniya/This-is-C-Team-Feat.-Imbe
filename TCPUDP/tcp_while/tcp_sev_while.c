#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <memory.h>

#define SERV_TCP_PORT 7000

int main(void){
	int sockfd, newsockfd, clilen;
	int size;
	int val_set;
	
	char buff[30];
	
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	
	

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
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val_set, sizeof(val_set));

	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		puts("Server : Can't bind Local Address.");
		exit(-1);
	}


	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	//printf("11  \n");

	
		
	memset(buff,0,30);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

	//printf("222\n");		

	if(newsockfd < 0)
	{
		puts("Server : accept error!");
		exit(-1);
	}

		//printf("333\n");

	while(1)
	{
		if((size = read(newsockfd, buff, 20)) <= 0)
		{
			puts("Server : readn error!");
			exit(-1);
		}

		printf("reading newsockfd from Client = %d\n", size);
		printf("Server : Received String = %s \n", buff);
	}
	
	close(newsockfd);
	

	close(sockfd);
	
	return 0;
}			
