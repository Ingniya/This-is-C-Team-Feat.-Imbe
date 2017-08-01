#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <memory.h>

#define SERV_TCP_PORT 7777
#define BUFSIZE 1024	

int main(int argc, char* argv[])
{
	int sockfd;
	int clilen, recvlen;
	
	char Buff[BUFSIZE];
	
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		puts("Server : Can't open Stream Socket.");
		exit(1);
	}
	
	memset(&serv_addr, 0 ,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		puts("Server : Can't bind Local Address.");
		exit(1);
	}
	
	
	
	while(1)
	{
		
		clilen = sizeof(cli_addr);
		
		
		
		
		
		
		
		if((recvlen=recvfrom(sockfd, Buff, BUFSIZE-1, 0, (struct sockaddr*)&cli_addr, \
		&clilen)) <0)
		{
			perror("Server : Receive error!");
			exit(1);
		}
		
		Buff[recvlen] = '\0';
		
		printf("clntPort : %d\n", ntohl(cli_addr.sin_port));
		
		printf("Received : %s\n", Buff);
		
		
		if(sendto(sockfd, Buff, recvlen, 0, (struct sockaddr*)&cli_addr,\
		sizeof(cli_addr)) != recvlen)
		{
			perror("Server : Sendto error!");
			exit(1);
		}
		
		
	
		
	}
	
	close(sockfd);
	
	return 0;
	
}