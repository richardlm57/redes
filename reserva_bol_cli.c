/* 
 * reserva_bol_cli.c
 *
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Archivo con la implementación del cliente del sistema de reserva de boletos
 *
 */

#include "reserva_bol_cli.h"

int main(int argc, char *argv[]){

	/* Verificación de argumentos de entrada */ 
	if ((argc!=8) || (strcmp(argv[2],"-p")!=0) || (strcmp(argv[4],"-f")!=0) || (strcmp(argv[6],"-c")!=0)
		|| (atoi(argv[5]) > 10) || (atoi(argv[5]) < 1) || (atoi(argv[7]) > 4) || (atoi(argv[7]) < 1)){
		perror("Error en argumentos");
		exit(-1);
	}

	/* Declaración e inicialización de variables*/
	int socketfd; 	// Socket de conexión con el servidor
	int i=0;		// Contador
	struct sockaddr_in serveraddr;	// Estrucutra con los parámetros del servidor
	int done=1;		// Booleano para indicar que la reserva fue hecha (o no)
	int row=0;		// Fila por stdin
	int column=0;	// Columna por stdin
	char buffer[256];	// Buffer para el mensaje
	int localport = atoi(argv[3]);	// Puerto de conexión

	bzero((char *) &serveraddr, sizeof(serveraddr));
	bzero(buffer,256);

	buffer[0]=atoi(argv[5]);
	buffer[1]=atoi(argv[7]);

	/* Especificación del servidor */
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	serveraddr.sin_port = htons(localport);

	/* Creación de socket */
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error en socket()\n");
		exit(-1);
	}

	/* Inicio de conexión con el servidor */
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

	/* Escribir al servidor */
	if (write(socketfd, buffer, strlen(buffer)) < 0){
		perror("Error en write()\n");
		exit(-1);
	}

	bzero(buffer,256);

	/* Lectura del servidor */  
	if (read(socketfd, buffer, 255)< 0){
		perror("Error en read()\n");
		exit(1);
	}

	printf("%s\n",buffer);

	/* Si el asiento solicitado estaba ocupado, se solicita nuevamente el asiento */
	if (buffer[0]=='O'){
		done=0;
	}

	while (!(done)){
		done=1;
		bzero(buffer,256);
		/* Fila y columna por stdin */
		printf("Introduce fila: \n");
		scanf("%d", &row);
		printf("Introduce columna: \n");
		scanf("%d", &column);
		buffer[0]=row;
		buffer[1]=column;
		/* Verificación de fila y columna */
		if ((row > 10) || (row < 1) || (column > 4) || (column < 1)){
			printf("Error en argumentos\n");
			done=0;
		}
		else{
			/* Se repite el proceso de conexión, escritura y lectura */
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
  
			if (write(socketfd, buffer, strlen(buffer)) < 0){
				perror("Error en write()\n");
				exit(-1);
			}

			bzero(buffer,256);
 
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