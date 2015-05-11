#include "reserva_bol_ser.h"

int main(int argc, char *argv[]){

	if ((argc!=7) || (strcmp(argv[1],"-f")!=0) || (strcmp(argv[3],"-c")!=0) || (strcmp(argv[5],"-p")!=0)) {
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd, accepted;
	int localport=atoi(argv[6]);
	int train[10][4]={{0}};
	int i,j;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t size;
	pid_t pid;
	char buffer[256] = {0};
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
	//serveraddr.sin_addr.s_addr = localhostaddress;
	serveraddr.sin_port = htons(localport);

	printf("Haciendo bind\n");
	if(bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0) {
		perror("Error en bind()\n");
		exit(-1);
	}

	printf("Escuchando\n");
	listen(socketfd,3);

	for (i=0;i<10;i++){
		for (j=0;j<4;j++){
			printf("%d ",train[i][j]);
		}
		printf("\n");
	}

	while (1){
		bzero((char *) &clientaddr, sizeof(clientaddr));
		size=sizeof(clientaddr);
		accepted = accept(socketfd, (struct sockaddr *)&clientaddr, &size);
		if (accepted < 0) {
			perror("Error en accept()\n");
			exit(-1);
		}
		if (read(accepted,buffer,255) < 0){		
			perror("Error en read()\n");
			exit(-1);
		}

		printf("%d%d\n",buffer[0],buffer[1]);

		if (train[buffer[0]-1][buffer[1]-1]==0){
			printf("%s\n",train);
			train[buffer[0]-1][buffer[1]-1]=1;
			if (write(accepted,"Reservado",9) < 0){
				perror("Error en write()\n");
				exit(-1);
			}
			//close(socketfd);
			close(accepted);
		}

		else{
			if (write(accepted,"Ocupado",8) < 0){
				perror("Error en write()\n");
				exit(-1);
			}
		}
		for (i=0;i<10;i++){
			for (j=0;j<4;j++){
				printf("%d ",train[i][j]);
			}
			printf("\n");
		}
		/*
		if ((pid=fork())==0){
			sprintf(inisocket,"%d",socketfd);
			sprintf(accsocket,"%d",accepted);
			if(execlp("./servicio","servicio",inisocket,accsocket,train,NULL)<0){
				perror("exec: ");
				exit(1);
			}*/
	}	  
	exit(0);
}