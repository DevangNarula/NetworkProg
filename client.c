// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define SERV_PORT 18080
#define MAXLINE 1024
#define SA struct sockaddr

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	bzero(&sendline,sizeof(sendline));
	while (fgets(sendline, MAXLINE, fp) != NULL) 
	{
		
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		bzero(&recvline,sizeof(recvline));
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = '\0'; /* null terminate */
		printf("Message from Server - %s",recvline);
		// fputs(recvline, stdout);
	}
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc != 2)
	  {
	     printf("Not found: IP address as CLI");
	     exit(0);
	  }   
	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
	close(sockfd);
	exit(0);
}
