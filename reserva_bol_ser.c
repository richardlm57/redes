/* 
 * reserva_bol_ser.c
 *
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Archivo con la implementación del servidor del sistema de reserva de boletos
 *
 */

#include "reserva_bol_ser.h"

/* Variables globales */
int train[10][4]={{0}};		// Matriz que representa los asientos del vagón
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 	// Mutex para acceder a la matriz

/* Función que ejecutará el hilo */
void* servicio(void *p){
	int sock = ((param*)p)->speak; // Socket por el que "hablará" el servidor
	char buffer[170];	// Buffer para el mensaje enviado por el cliente
	char message[170];	// Buffer para el mensaje que enviará el servidor
	char temp[6];		// Variable temporal para almacenar asientos del vagón
	int i,j,row,column;	// Variables para fila y columna 
	
	/* Variables para obtener la fecha actual */
	time_t rawtime;
	struct tm *info;
	char date[80];
	char *token;

	time( &rawtime );
	info = localtime( &rawtime );
	strcpy(date,asctime(info));
	token = strtok(date, "\n");

	/* Archivo de log */
	FILE *f = fopen("log-server", "a");
	if (f == NULL){
	    perror("Error al abrir el archivo\n");
	}

	/* Disponibilidad del asiento */
	while( read(sock,buffer,170) ){
		row=buffer[0];
		column=buffer[1];
		/* Si el asiento está disponible, se ocupa y la reserva es exitosa */
		if (train[buffer[0]-1][buffer[1]-1]==0){
			pthread_mutex_lock(&mutex);
			train[buffer[0]-1][buffer[1]-1]=1;
			pthread_mutex_unlock(&mutex);
			/* Se escribe en el log y se cierra el archivo de log */
			fprintf(f,"[%s] [respuesta] [cliente %s]: Puesto fila %d columna %d reservado.\n",
			token, ((param*)p)->ip,row,column);
			fclose(f);
			/* El servidor envía el mensaje */
			if (write(sock,"Reservado",9) < 0){
				perror("Error en write()\n");
				exit(-1);
			}
		}
		/* Si el asiento no está disponible, se verifica la disponibilidad de otros asientos */
		else{			
			strcpy(buffer,"");
			for (i=0;i<10;i++){
				for (j=0;j<4;j++){
					if (train[i][j]==0){
						sprintf(temp,"%d %d\n",i+1,j+1);
						strcat(buffer,temp);
					}
				}
			}
			/* Si no hay ningún asiento disponible, se envía el mensaje de vagón completo */
			if ((strcmp(buffer,"")==0)){
				/* Se escribe en el log y se cierra el archivo de log */
				fprintf(f,"[%s] [respuesta] [cliente %s]: Vagón completo.\n",token, ((param*)p)->ip);
				fclose(f);
				/* El servidor envía el mensaje */
				if (write(sock,"Vagón completo",15) < 0){
					perror("Error en write()\n");
					exit(-1);
				}
			}
			/* Si hay algún asiento disponible, se envía la lista de asientos disponibles */
			else{
				/* Se escribe en el log y se cierra el archivo de log */
				fprintf(f,"[%s] [respuesta] [cliente %s]: Puesto fila %d columna %d ocupado.\n",
				token, ((param*)p)->ip,row,column);				
				fclose(f);
				strcpy(message,"Ocupado\n");
				strcat(message,buffer);
				/* El servidor envía el mensaje */
				if (write(sock,message,strlen(message)) < 0){
					perror("Error en write()\n");
					exit(-1);
				}
			}
		}
	}
	/*
	for (i=0;i<10;i++){
		for (j=0;j<4;j++){
			printf("%d ",train[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	/* Se cierra el socket de habla */
	close(sock);
	free(p);
	p=NULL;
}

int main(int argc, char *argv[]){

	/* Verificación de argumentos de entrada */ 
	if ((argc!=7) || (strcmp(argv[1],"-f")!=0) || (strcmp(argv[3],"-c")!=0) || (strcmp(argv[5],"-p")!=0)) {
		perror("Error en argumentos");
		exit(-1);
	}

	/* Declaración e inicialización de variables*/
	int socketfd, accepted;	// Sockets de habla y escucha
	int localport=atoi(argv[6]);	// Puerto de conexión
	int i,j;	// Contadores
	struct sockaddr_in serveraddr, clientaddr;	// Estructuras para el cliente y el servidor
	socklen_t size;	// Tamaño para la estructura anterior
	struct hostent* localhost = gethostbyname("localhost");
	bzero((char *) &serveraddr, sizeof(serveraddr));
	bzero((char *) &clientaddr, sizeof(clientaddr));
	size=sizeof(clientaddr);
	pthread_t t;	// Hilo
	param *p;		// Estructura para la función del hilo
	p=NULL;

	/* Creación de socket */
	if ((socketfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {  
		perror("Error en socket()\n");
		exit(-1);
	}

	/* Especificación del servidor */
	serveraddr.sin_family = AF_INET;
	bcopy((char *)localhost->h_addr, (char *)&serveraddr.sin_addr.s_addr, localhost->h_length);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(localport);

	/* Asociación de socket con dirección */
	if(bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0) {
		perror("Error en bind()\n");
		exit(-1);
	}

	/* Escucha de clientes */
	listen(socketfd,100);

	
	/*
	for (i = 0; i < 10; i++)
	for ( j = 0; j < 4; j++)
	train[i][j] = 1;
	*/

	/* Aceptación de conexiones */
	while (accepted = accept(socketfd, (struct sockaddr *)&clientaddr, &size)){
		if (accepted < 0) {
			perror("Error en accept()\n");
			exit(-1);
		}
		/* Se inicializa la estructura necesaria para que el hilo ejecute su función */
		p = (param*)calloc(1,sizeof(param));
		p->speak=accepted;
		p->ip=inet_ntoa(clientaddr.sin_addr);
		/* Creación del hilo */
		if (pthread_create(&t,NULL,servicio,(void *)p)){
			perror("pthread_create");
			exit(-1);
		}
	}
	/* Cierre del socket de escucha */
	close(socketfd);
	exit(0);
}