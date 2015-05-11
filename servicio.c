/* 	argv[1] socket de socket()
	argv[2] socket de accept()
	argv[3] vagon del tren
*/

#include "reserva_bol_ser.h"

int main(int argc, char *argv[]){
	char buffer[256] = {0};
	close(atoi(argv[1]));
	if (read(atoi(argv[2]),buffer,255) < 0){		
		perror("Error en read()\n");
		exit(-1);
	}

	printf("%d%d\n",buffer[0],buffer[1]);

	if (argv[3][(4*buffer[0]+buffer[1])-1]=='0'){
		printf("%s\n",argv[3]);
		argv[3][(4*buffer[0]+buffer[1])-1]='1';
		if (write(atoi(argv[2]),"Reservado",9) < 0){
			perror("Error en write()\n");
			exit(-1);
		}
		printf("%s\n",argv[3]);
	}

	else{
		if (write(atoi(argv[2]),"dame deso",9) < 0){
			perror("Error en write()\n");
			exit(-1);
		}
	}
	close(atoi(argv[2]));
	exit(0);
}