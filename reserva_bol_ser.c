#include "reserva_bol_ser.h"

int main(int argc, char *argv[]){

	if ((argc!=7) || (strcmp(argv[1],"-f")!=0) || (strcmp(argv[3],"-c")!=0) || (strcmp(argv[5],"-p")!=0)) {
		perror("Error en argumentos");
		exit(-1);
	}

	int socketfd, accepted;
	char *inisocket = (char*)malloc(32*sizeof(char));
	char *accsocket = (char*)malloc(32*sizeof(char));
	int localport=atoi(argv[6]);
	char train[40]={0};
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t size;
	pid_t pid;
	struct hostent* localhost = gethostbyname("localhost");
	/* Esta parte no la entiendo mucho, ni aqui ni en el cliente
	int localhostaddress;
    memcpy( &localhostaddress, localhost->h_addr, localhost->h_length );*/
    bzero((char *) &serveraddr, sizeof(serveraddr));
    strcpy(train,"0000000000000000000000000000000000000000");
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
	printf("%s\n",train);
	listen(socketfd,3);
	while (1){
		bzero((char *) &clientaddr, sizeof(clientaddr));
		size=sizeof(clientaddr);
		accepted = accept(socketfd, (struct sockaddr *)&clientaddr, &size);
		if (accepted < 0) {
			perror("Error en accept()\n");
			exit(-1);
		}
		if ((pid=fork())==0){
			sprintf(inisocket,"%d",socketfd);
			sprintf(accsocket,"%d",accepted);
			if(execlp("./servicio","servicio",inisocket,accsocket,train,NULL)<0){
				perror("exec: ");
				exit(1);
			}
		close(accepted);
		}
	}	  
	exit(0);
}