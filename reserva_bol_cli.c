#include "reserva_bol_cli.h"

int main(int argc, char *argv[]){
	if ((argc!=8) || (strcmp(argv[2],"-p")!=0) || (strcmp(argv[4],"-f")!=0) || (strcmp(argv[6],"-c")!=0)
		|| (atoi(argv[5]) > 10) || (atoi(argv[5]) < 1) || (atoi(argv[7]) > 4) || (atoi(argv[7]) < 1)){
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd;
	int i=0;
	struct sockaddr_in serveraddr;
	int done=1;
	int row=0;
	int column=0;
	char buffer[256];

	int localport = atoi(argv[3]);

	bzero((char *) &serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	serveraddr.sin_port = htons(localport);

	//Input
	bzero(buffer,256);
	buffer[0]=atoi(argv[5]);
	buffer[1]=atoi(argv[7]);

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error en socket()\n");
		exit(-1);
	}

	while (i<3){
		if (connect(socketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) >= 0){
			break;
		}
		if (i==2){
			perror("Se ha agotado el tiempo de espera");
			exit(-1);
		}
		i++;
	}

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

	if (buffer[0]=='O'){
		done=0;
	}

	while (!(done)){
		done=1;
		bzero(buffer,256);
		printf("Introduce fila: \n");
		scanf("%d", &row);
		printf("Introduce columna: \n");
		scanf("%d", &column);
		buffer[0]=row;
		buffer[1]=column;
		if ((row > 10) || (row < 1) || (column > 4) || (column < 1)){
			printf("Error en argumentos\n");
			done=0;
		}
		else{
			if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
				perror("Error en socket()\n");
				exit(-1);
			}
			while (i<3){
				if (connect(socketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) >= 0){
					break;
				}
				if (i==2){
					perror("Se ha agotado el tiempo de espera");
					exit(-1);
				}
				i++;
			}

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

			if (buffer[0]=='O'){
				done=0;
			}
		}
	}

	exit(0);
}