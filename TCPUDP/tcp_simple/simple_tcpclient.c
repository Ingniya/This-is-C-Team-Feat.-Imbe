#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>

#define SERV_TCP_PORT 7000
#define SERV_HOST_ADDR "192.168.0.8"

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serv_addr;
	bzero((void *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

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

	if(write(sockfd, "How is the weather?", 20) < 20)
	{
		puts("Client : writen error");
		exit(-1);
	}

	close(sockfd);

	return 0;
}

