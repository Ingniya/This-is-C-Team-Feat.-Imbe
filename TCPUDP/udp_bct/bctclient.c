#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>

#define SERV_TCP_PORT 7777
#define SERV_HOST_ADDR "192.168.0.8"
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	int recvlen, servlen, sockopt;

	char SendBuffer[BUFSIZE], RecvBuffer[BUFSIZE];
	
	struct sockaddr_in serv_addr;

	
	if(argc != 2)
	{
		printf("%s <port>", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		puts("Client : Can't open stream socket.");
		exit(1);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	

	sockopt=1;
	
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &sockopt, sizeof(sockopt));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	serv_addr.sin_port = htons((short)atoi(argv[1]));
	
	while(1)
	{
		printf("Input Sending Message ==> ");
		fgets(SendBuffer, BUFSIZE, stdin);
		
		if(!strncmp(SendBuffer,"quit",4))
			break;
		
		if(sendto(sockfd, SendBuffer, strlen(SendBuffer), 0, (struct sockaddr*)&serv_addr,\
		sizeof(serv_addr)) != strlen(SendBuffer))
		{
			perror("Sento error!");
			exit(1);
		}
		
		//servlen = sizeof(servlen);
		
		
		if((recvlen = recvfrom(sockfd, RecvBuffer, BUFSIZE-1, 0, (struct sockaddr*)&serv_addr,\
		&servlen)) != strlen(SendBuffer))
		{
			perror("recvfrom error!");
			exit(1);
		}
		
		RecvBuffer[recvlen]='\0';
		
		printf("Received : %s \n", RecvBuffer);
		
	}
	
	close(sockfd);
	exit(0);
}

