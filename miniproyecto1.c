#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(){
	int socketfd, localport, bindsuccess;
	struct sockaddr_in socketbind;

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
	if((bindsuccess=bind(socketfd,(struct sockaddr*)&socketbind,sizeof(socketbind))) < 0) {
		printf("Error en bind() \n");
		exit(-1);
	}
	printf("Bind del carajo: %d\n",bindsuccess);
}