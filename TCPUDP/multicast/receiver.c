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

struct sockaddr_in localsock;
struct ip_mreq group;

int sockfd;
int datalen;

char buff[1024];

int main(int argc, char *argv[])
{
	struct sockaddr_in peeraddr;
	int addrlen = sizeof(peeraddr);
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Receiver : Opening Error!");
		exit(1);
	}
	
	int reuse = 1;
	
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
	{
		perror("Receiver : Setting SO_REUSEADDR Error!");
		close(sockfd);
		exit(1);
	}
	
	printf("Reuse\n");
	
	memset((char *)&localsock, 0, sizeof(localsock));
	localsock.sin_family = AF_INET;
	localsock.sin_port = htons(GROUP_PORT);
	localsock.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sockfd, (struct sockaddr*)&localsock, sizeof(localsock)))
	{
		perror("Receiver : Binding Datagram Error!");
		close(sockfd);
		exit(1);
	}
	
	printf("Receiver : Binding Success!\n");
	
	group.imr_multiaddr.s_addr=inet_addr(GROUP_ADDRESS);
	group.imr_interface.s_addr=inet_addr(LOCAL_INTERFACE);
	
	if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group,\
	sizeof(group)) < 0)
	{
		perror("Receiver : Adding Multicast Group Error!");
		close(sockfd);
		exit(1);
	}
	printf("Join Success!!\n");
	
	
	while(1)
	{
		datalen = sizeof(buff);
		
		printf("Datalen : %d\n",datalen);
		
		if(recvfrom(sockfd, buff, datalen, 0, (struct sockaddr*)&peeraddr, &addrlen) < 0)
		{
			perror("Receiver : Reading Datagram Error!");
			close(sockfd);
			exit(1);
		}
		
		printf("Receiver : Databuf : %s\n", buff);
	}
	setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&group, sizeof(group));
	
	close(sockfd);
	return 0;
	
}
	