/*
 * rdisponible.c
 */

#include <stdio.h>
#include <rpc/rpc.h>
#include "disp.h" 

 int main(int argc, char const *argv[])
 {
 	
 	CLIENT *cl;
 	int *result;
 	char *server;
 	char *message;

 	if (argc < 3) {

 	}

 	fila = argv[1];
 	columna = argv[2];

 	/* Creates the client handle used for calling DISPONIBLEPROG
 	*/

 	cl = clnt_create (server, DISPONIBLEPROG, DISPONIBLEVERS, "tcp");
 	if (cl == NULL) {
 		/* Couldn't establish connection with server.*/
 		clnt_pcreateerror(server);
 		exit(1);
 	}

 	/* Call the remote procedure disponible_1 on the server */

 	result = disponible_1 (&fila, &columna, cl);

 	if (result == NULL) {

 		/*An error ocurred while calling the server*/
 		clnt_perror(cl,server);
 		exit(1);
 	}

 	if (*result == 0) {
 		/* Ocupado */

 		printf("%s Está ocupado\n", fila);
 		exit (1);
 	}

 	else {
 		printf("%s Reservado\n", fila);
 	}



 	return 0;
 }