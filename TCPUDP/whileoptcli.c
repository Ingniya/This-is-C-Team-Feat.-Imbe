#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>

#define SERV_TCP_PORT 8000
#define SERV_HOST_ADDR "192.168.0.8"
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int sockfd, len_l;
	
	struct sockaddr_in serv_addr;
	struct linger ling_get;
	struct linger ling_set;
	
	char buff[BUFSIZE];
	
	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		puts("Client : Can't open stream socket.");
		exit(-1);
	}

	ling_set.l_onoff = 1;
	ling_set.l_linger = 5;
	
	setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (void *)&ling_set, sizeof(ling_set));
	getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling_get, &len_l);
	
	printf("After set linger %d %d \n", ling_get.l_onoff, ling_get.l_linger);
	
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		puts("Client : Can't connect the server.");
		exit(-1);
	}
	
	while(1)
	{
		printf("Input : ");
		fgets(buff,BUFSIZE,stdin);
		
		if(!strncmp(buff,"quit",4))
			break;
		
		if(write(sockfd, "How is the weather?", 20) < 20)
		{
			puts("Client : writen error");
			exit(-1);
		}
		
	}
	
	

	close(sockfd);

	return 0;
}

