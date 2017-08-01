#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <memory.h>

#define SERV_TCP_PORT 7777
#define SERV_HOST_ADDR "192.168.0.8"
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	int recvlen, servlen;

	char SendBuffer[BUFSIZE], RecvBuffer[BUFSIZE];
	
	struct sockaddr_in serv_addr;

	
	if(argc != 2)
	{
		fprintf(stderr, "Usage : %s IP_address\n", argv[0]);
		exit(1);
	}
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		puts("Client : Can't open stream socket.");
		exit(1);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	
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
		
		servlen = sizeof(servlen);
		
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

