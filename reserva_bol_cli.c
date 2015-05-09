#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[]){
	int socketfd;
	struct sockaddr_in serveraddr;
	struct hostent *server;

	char* buffer;

	int localport = 32000;

	bzero((char *) &serveraddr, sizeof(serveraddr));

	printf("pase");

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error en socket()\n");
		exit(-1);
	}

	if ((server = gethostbyname("localhost")) == NULL) {
		perror("Error localizando el servidor\n");
		exit(-1);
	}

	serveraddr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
	serveraddr.sin_port = htons(localport);

	if (connect(socketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
		perror("Error en connect()\n");
		exit(-1);
	}

	//Input
	bzero(buffer,256);
	fgets(buffer,255,stdin);

	//Escribir al servidor   
	if (write(socketfd, buffer, strlen(buffer)) < 0){
		perror("Error en write()\n");
		exit(-1);
	}

	bzero(buffer,256);

	//Lectura del servidor  
	if (read(socketfd, buffer, 255)< 0){
		perror("Error en read()\n");
		exit(1);
	}
	
	printf("%s\n",buffer);
	exit(0);
}