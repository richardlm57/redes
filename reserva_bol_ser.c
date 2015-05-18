#include "reserva_bol_ser.h"

int train[10][4]={{0}};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* servicio(void *p){
	int sock = ((param*)p)->speak;
	int read_size;
	char buffer[170];
	char message[170];
	char temp[6];
	int i,j,row,column;
	
	time_t rawtime;
	struct tm *info;
	char date[80];
	char *token;

	time( &rawtime );
	info = localtime( &rawtime );
	strcpy(date,asctime(info));
	token = strtok(date, "\n");

	FILE *f = fopen("log-server", "a");
	if (f == NULL){
	    perror("Error al abrir el archivo\n");
	}

	while( read(sock,buffer,170) ){
		row=buffer[0];
		column=buffer[1];
		printf("%d%d\n",buffer[0],buffer[1]);
		if (train[buffer[0]-1][buffer[1]-1]==0){
			pthread_mutex_lock(&mutex);
			train[buffer[0]-1][buffer[1]-1]=1;
			pthread_mutex_unlock(&mutex);
			fprintf(f,"[%s] [respuesta] [cliente %s]: Puesto fila %d columna %d reservado.\n",
			token, ((param*)p)->ip,row,column);
			fclose(f);
			if (write(sock,"Reservado",9) < 0){
				perror("Error en write()\n");
				exit(-1);
			}
		}
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
			if ((strcmp(buffer,"")==0)){
				fprintf(f,"[%s] [respuesta] [cliente %s]: Vagón completo.\n",token, ((param*)p)->ip);
				fclose(f);
				if (write(sock,"Vagón completo",15) < 0){
					perror("Error en write()\n");
					exit(-1);
				}
			}
			else{
				fprintf(f,"[%s] [respuesta] [cliente %s]: Puesto fila %d columna %d ocupado.\n",
				token, ((param*)p)->ip,row,column);				
				fclose(f);
				strcpy(message,"Ocupado\n");
				strcat(message,buffer);
				if (write(sock,message,strlen(message)) < 0){
					perror("Error en write()\n");
					exit(-1);
				}
			}
		}
	}
	for (i=0;i<10;i++){
		for (j=0;j<4;j++){
			printf("%d ",train[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	close(sock);
	free(p);
	p=NULL;
}

int main(int argc, char *argv[]){

	if ((argc!=7) || (strcmp(argv[1],"-f")!=0) || (strcmp(argv[3],"-c")!=0) || (strcmp(argv[5],"-p")!=0)) {
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd, accepted;
	int localport=atoi(argv[6]);
	int i,j;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t size;
	struct hostent* localhost = gethostbyname("localhost");
	bzero((char *) &serveraddr, sizeof(serveraddr));
	printf("Creando socket\n");
	if ((socketfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {  
		perror("Error en socket()\n");
		exit(-1);
	}

	serveraddr.sin_family = AF_INET;
	bcopy((char *)localhost->h_addr, (char *)&serveraddr.sin_addr.s_addr, localhost->h_length);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(localport);

	printf("Haciendo bind\n");
	if(bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0) {
		perror("Error en bind()\n");
		exit(-1);
	}

	printf("Escuchando\n");
	listen(socketfd,100);

	bzero((char *) &clientaddr, sizeof(clientaddr));
	size=sizeof(clientaddr);
	
	/*
	for (i = 0; i < 10; i++)
	for ( j = 0; j < 4; j++)
	train[i][j] = 1;
	*/

	while (accepted = accept(socketfd, (struct sockaddr *)&clientaddr, &size)){
		if (accepted < 0) {
			perror("Error en accept()\n");
			exit(-1);
		}
		printf("Entre\n");
		pthread_t t;

		param *p;
		p=NULL;
		p = (param*)calloc(1,sizeof(param));
		p->speak=accepted;
		p->ip=inet_ntoa(clientaddr.sin_addr);
		if (pthread_create(&t,NULL,servicio,(void *)p)){
			perror("pthread_create");
			exit(-1);
		}
	}
	close(socketfd);
	exit(0);
}