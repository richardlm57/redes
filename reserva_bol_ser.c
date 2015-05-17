#include "reserva_bol_ser.h"

int train[10][4]={{0}};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* servicio(void *speak){
	int sock = *(int*)speak;
	int read_size;
	char buffer[170];
	char message[170];
	char temp[6];
	int i,j;
	while( read(sock,buffer,170) ){
		printf("%d%d\n",buffer[0],buffer[1]);
		if (train[buffer[0]-1][buffer[1]-1]==0){
			pthread_mutex_lock(&mutex);
			train[buffer[0]-1][buffer[1]-1]=1;
			pthread_mutex_unlock(&mutex);
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
			printf("%s\n",buffer);
			if ((strcmp(buffer,"")==0)){
				if (write(sock,"Vagón completo",15) < 0){
					perror("Error en write()\n");
					exit(-1);
				}
			}
			else{
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
	free(speak);
	speak=NULL;
}

int main(int argc, char *argv[]){

	if ((argc!=7) || (strcmp(argv[1],"-f")!=0) || (strcmp(argv[3],"-c")!=0) || (strcmp(argv[5],"-p")!=0)) {
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd, accepted, *speak;
	int localport=atoi(argv[6]);
	int i,j;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t size;
	struct hostent* localhost = gethostbyname("localhost");
	/* Esta parte no la entiendo mucho, ni aqui ni en el cliente
	int localhostaddress;
    memcpy( &localhostaddress, localhost->h_addr, localhost->h_length );*/
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
		speak=(int *)malloc(sizeof(int));
		*speak=accepted;
		
		if (pthread_create(&t,NULL,servicio,(void *)speak)){
			perror("pthread_create");
			exit(-1);
		}
	}
	exit(0);
}