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


int main(){
	int socketfd, accepted;
	int localport=32000;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t size;
	char* buffer;
	
	struct hostent* localhost = gethostbyname( "localhost" );
	/*
	int localhostaddress;
    memcpy( &localhostaddress, localhost->h_addr, localhost->h_length );*/

    bzero((char *) &serveraddr, sizeof(serveraddr));

	printf("Creando socket\n");
	if ((socketfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {  
		printf("Error en socket()\n");
		exit(-1);
	}
	printf("Socket: %d\n",socketfd);

	serveraddr.sin_family = AF_INET;
	bcopy((char *)localhost->h_addr, (char *)&serveraddr.sin_addr.s_addr, localhost->h_length);
	//serveraddr.sin_addr.s_addr = localhostaddress;
	serveraddr.sin_port = htons(localport);

	printf("Haciendo bind\n");
	if(bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0) {
		printf("Error en bind()\n");
		exit(-1);
	}

	printf("Escuchando\n");
	if (listen(socketfd,5) != 0){
		printf("Error en listen()\n");
		exit(-1);
	}

	for (;;){
		bzero((char *) &clientaddr, sizeof(clientaddr));
		size=sizeof(clientaddr);
		accepted = accept(socketfd, (struct sockaddr *)&clientaddr, &size);
		if (accepted < 0) {
			perror("Error en accept()\n");
			exit(-1);
		}

		bzero(buffer,256);

		/*
		if (read( accepted,buffer,255 ) < 0){		
			perror("Error en read()\n");
			exit(-1);
		}

		if (write(accepted,"I got your message",18) < 0){
			perror("Error en write()\n");
			exit(-1);
		}*/
	}	  
	exit(0);
}