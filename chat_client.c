#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	int clientsock ;
	struct sockaddr_in servaddr ;
	char msg[100];
	
	// creating a socket
	clientsock = socket(PF_INET,SOCK_STREAM,0);
	
	// clearing buffer for server address
	bzero(&servaddr,sizeof(servaddr));
	
	// setting server family , address and port no.
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(2008);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if( connect(clientsock,(struct sockaddr *) &servaddr, sizeof(servaddr)) != -1 )
	{
		printf("Connection established \n");
		while(1)
		{
			bzero(&msg,sizeof(msg)) ;
			fgets(msg,sizeof(msg),stdin); // input from user
			send(clientsock,msg,strlen(msg),0); // sending message to server
			
			bzero(&msg,sizeof(msg)) ;
			recv(clientsock,msg,sizeof(msg),0); // receiving message from client
			printf(" Message from Server : %s \n",msg);
			
		}
		
		// closing the socket
		close(clientsock);
	}
	else
	{
		printf("Failed to connect to server \n");
	}
	
	
	
	return 0;
}
