#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	int servsock , clientsock ;
	struct sockaddr_in servaddr ;
	char msg[100];
	
	// creating a socket
	servsock = socket(PF_INET,SOCK_STREAM,0);
	
	// clearing buffer for server address
	bzero(&servaddr,sizeof(servaddr));
	
	// setting server family , address and port no.
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(2008);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// binding socket with server address
	bind(servsock,(struct sockaddr *) &servaddr,sizeof(servaddr));
	
	listen(servsock,10); // calling listen system call
	printf("server is in listening mode \t waiting for new connection ... \n\n");
	
	// accepting the client connection
	clientsock = accept(servsock,(struct sockaddr *) NULL , NULL);
	if(clientsock != -1)
	{
		printf("connection established ! \n");
		while(1)
		{
			bzero(&msg,sizeof(msg)) ;
			recv(clientsock,msg,sizeof(msg),0); // receiving message from client
			
			printf(" Message from Client : %s \n",msg);
			
			send(clientsock,msg,strlen(msg),0); // sending message to client
			
		}
		
		// closing the sockets 
		close(clientsock);
	}
	else
	{
		printf("Failed to accept connection ! \n");
	}
	close(servsock);
	
	return 0;
}

