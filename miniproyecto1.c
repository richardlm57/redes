#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
	int socketfd, localport, acceptsock, n;
	struct sockaddr_in socketbind, clientaddr;
	char* buffer;

	localport=32000;
	struct hostent* localhost = gethostbyname( "localhost" );
    long localhostaddress;
    memcpy( &localhostaddress, localhost->h_addr, localhost->h_length );


	printf("Creando socket\n");
	if ((socketfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {  
		printf("Error en socket()\n");
		exit(-1);
	}
	printf("Socket: %d\n",socketfd);

	bzero((char *) &socketbind, sizeof(socketbind));
	socketbind.sin_family = AF_INET;
	socketbind.sin_addr.s_addr = localhostaddress;
	socketbind.sin_port = htons(localport);

	printf("Haciendo bind\n");
	if(bind(socketfd,(struct sockaddr*)&socketbind,sizeof(socketbind)) < 0) {
		printf("Error en bind() \n");
		exit(-1);
	}

	printf("Escuchando\n");
	if (listen(socketfd,5) != 0){
		printf("Error en listen() \n");
		exit(-1);
	}

	for (;;){
		/* Accept actual connection from the client */
		acceptsock = accept(socketfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		if (acceptsock < 0){
			perror("Error en accept");
			exit(-1);
		}

		/* If connection is established then start communicating */
		bzero(buffer,256);
		n = read( acceptsock,buffer,255 );

		if (n < 0)
		{
			perror("ERROR reading from socket");
			exit(1);
		}

		printf("Here is the message: %s\n",buffer);

		/* Write a response to the client */
		n = write(acceptsock,"I got your message",18);

		if (n < 0)
		{
			perror("ERROR writing to socket");
			exit(1);
		}
	}	  
	exit(0);
}