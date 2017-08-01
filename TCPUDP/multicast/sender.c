#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROUP_ADDRESS "239.168.205.100"
#define GROUP_PORT 5555
#define LOCAL_INTERFACE "192.168.205.26"

struct in_addr localinterface;
struct sockaddr_in groupsock;

int sockfd;
int datalen;
int multi_TTL=64;

char buff[30];

int main(int argc, char *argv[])
{
	int retval;
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM,0)) < 0)
	{
		perror("Sender : Opening error!");
		exit(1);
	}			
	
	printf("Sender : Socket Success\n");
	
	setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&multi_TTL, sizeof(multi_TTL));
	
	memset((char *)&groupsock, 0, sizeof(groupsock));
	
	groupsock.sin_family = AF_INET;
	groupsock.sin_addr.s_addr = inet_addr(GROUP_ADDRESS);
	groupsock.sin_port = htons(GROUP_PORT);
	
	localinterface.s_addr = inet_addr(LOCAL_INTERFACE);
	
	if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localinterface,\
	sizeof(localinterface)) < 0)
	{
		perror("Sender : Setting Local Interface Error!");
		close(sockfd);
		exit(1);
	}
	printf("Sender : IF Success!\n");
	
	char loopch = 0;
	
	if(setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_LOOP,(char *)&loopch, sizeof(loopch)) < 0)
	{
		perror("Sender : Setting IP_MULTICAST_LOOP : ");
		close(sockfd);
		exit(1);
	}
	
	printf("Loop Success!\n");
	
	while(1)
	{
		printf("Input(quit) :::: ");
		fgets(buff, 30, stdin);
		
		if(!strncmp(buff,"quit",4))
			break;
		
		datalen = sizeof(buff);
		
		if((retval = sendto(sockfd, buff, datalen, 0, (struct sockaddr *)&groupsock,\
		sizeof(groupsock))) < 0)
		{
			perror("Sender : Sending DataGram Error!");
			close(sockfd);
			exit(1);
		}
		
		printf("%d Byte Sent.\n", retval);
		sleep(3);
	}
	
	close(sockfd);
	return 0;
}