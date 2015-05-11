#include "reserva_bol_cli.h"

int main(int argc, char *argv[]){
	if ((argc!=8) || (strcmp(argv[2],"-p")!=0) || (strcmp(argv[4],"-f")!=0) || (strcmp(argv[6],"-c")!=0)
		|| (atoi(argv[5]) > 10) || (atoi(argv[5]) < 1) || (atoi(argv[7]) > 4) || (atoi(argv[7]) < 1)){
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd;
	int i=0;
	int done=1;
	int inputA=0;
	int inputB=0;
	struct sockaddr_in serveraddr;
	//struct hostent* server;

	char buffer[256];

	int localport = atoi(argv[3]);

	bzero((char *) &serveraddr, sizeof(serveraddr));

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error en socket()\n");
		exit(-1);
	}

	/*
	if ((server = gethostbyname("localhost")) == NULL) {
		perror("Error localizando el servidor\n");
		exit(-1);
	}*/

	serveraddr.sin_family = AF_INET;
	/*bcopy((char *)&server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
	printf("%d\n",serveraddr.sin_addr.s_addr);*/
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	serveraddr.sin_port = htons(localport);

	while (i<3){
		if (connect(socketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) >= 0){
			break;
		}
		if (i==3){
			perror("Se ha agotado el tiempo de espera");
			exit(-1);
		}
		i++;
	}

	//Input
	bzero(buffer,256);
	buffer[0]=atoi(argv[5]);
	buffer[1]=atoi(argv[7]);

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
	
	if (buffer[0]=='O'){
		done=0;
	}

	printf("%s\n",buffer);

	while (!(done)){
		bzero(buffer,256); 
		printf("Ingresa un valor para la fila: ");
		scanf("%d", &inputA);
		printf("Ingresa un valor para la columna: ");
		scanf("%d", &inputB);
		if ((inputA > 10) || (inputA < 1) || (inputB > 4) || (inputB < 1)){
			printf("Los valores son inválidos.");
			continue;
		}

		buffer[0]=inputA;
		buffer[1]=inputB;
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

		if (buffer[0]=='O'){
			done=0;
		}
		else{
			done=1;
		}
		printf("%s\n",buffer);
	}
	exit(0);
}