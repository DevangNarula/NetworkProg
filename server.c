// Server side implementation of UDP client-server model
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

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];
	for ( ; ; ) {
		len = clilen;
		bzero(&mesg,sizeof(mesg));
		n = recvfrom(sockfd, mesg, sizeof(mesg), 0, pcliaddr, &len);
		
		printf("Message from Client - %s",mesg);
		
		bzero(&mesg,sizeof(mesg));
		fgets(mesg,sizeof(mesg),stdin);	
		sendto(sockfd, mesg, sizeof(mesg), 0, pcliaddr, len);
	}
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
	close(sockfd);
}

