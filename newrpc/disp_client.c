/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */
#include <stdlib.h>
#include <stdio.h>
#include "disp.h"


void
disponibleprog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	int  disponible_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DISPONIBLEPROG, DISPONIBLEVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = disponible_1(&disponible_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	CLIENT *cl;
	int row;
	int *result_1;


	/* Verificación de los argumentos de entrada*/ 
	if ((argc != 4) || (strcmp(argv[2],"-f") != 0) || (strcmp(argv[4],"-c") != 0)){
		printf ("Error en los argumentos de entradas")
		exit (1);
	}

	/* Verificación de un valor válido para el número de fila*/
	if (atoi(argv[3]) > 10 || atoi(argv[3]) < 1 ){
		printf ("Error: Número de fila inválido")
		exit (1);
	}

	/* Verificación de un valor válido para el número de columna*/
	if (atoi(argv[5]) > 4 || atoi(argv[5]) < 1 ){
		printf ("Error: Número de columna inválido")
		exit (1);
	}

	host = argv[1];
	row = atoi(argv[3]);
	column = atoi(argv[5]);

	cl = clnt_create (host, DISPONIBLEPROG, DISPONIBLEVERS, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	result_1 = disponible_1(&row,cl);
	if (result_1 == (int *) NULL) {
		clnt_perror (cl, "call failed");
	}
	else{
		printf("%d\n",*result_1);
	}

	clnt_destroy(cl);
	exit (0);
}
