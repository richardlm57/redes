/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "reserva_bol.h"


void
reserva_bol_prog_2(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char * is_available_2_arg;
	char * *result_2;
	char *seats_2_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RESERVA_BOL_PROG, RESERVA_BOL_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = is_available_2(&is_available_2_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = seats_2((void*)&seats_2_arg, clnt);
	if (result_2 == (char **) NULL) {
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
	int column;
	int *result_1;
	char **result_2;
	char *vagon_1_arg;
	char *row_column;

	/* Verificación de los argumentos de entrada*/ 
	if ((argc != 6) ||(strcmp(argv[2],"-f") != 0)  || (strcmp(argv[4],"-c") != 0)){
		printf ("Error en los argumentos de entrada\n");
		exit (1);
	}

	/* Verificación de un valor válido para el número de fila*/
	else if (atoi(argv[3]) > 10 || atoi(argv[3]) < 1 ){
		printf ("Error: Número de fila inválido \n");
		exit (1);
	}

	/* Verificación de un valor válido para el número de columna*/
	else if (atoi(argv[5]) > 4 || atoi(argv[5]) < 1 ){
		printf ("Error: Número de columna inválido\n");
		exit (1);
	}

	/* Asignación de las variables de entrada*/
	host = argv[1];
	row = atoi(argv[3]);
	column = atoi(argv[5]);

	row_column = malloc(sizeof(char) * 4);

	/* Crea el cliente*/
	cl = clnt_create (host, RESERVA_BOL_PROG, RESERVA_BOL_VERS, "udp");
	if (cl == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	while (1){

		sprintf(row_column, "%d %d", row, column);
		/* Verifica si el puesto está disponible */
		result_1 = is_available_2(&row_column,cl);
		printf("%d\n", *result_1);

		if (result_1 == (int *) NULL) {
			clnt_perror (cl, "call failed");
			break;
		}
		/* Si el puesto está disponible*/
		else if (*result_1 == 1){
			printf("El puesto fila %d columna %d ha sido reservado\n", row, column);
			break;
		}
		/* Sino lo está*/
		else if (*result_1 == 0){
			
			result_2 = seats_2((void*)&vagon_1_arg,cl);

			if (result_2 == (char **) NULL) {
				clnt_perror (cl, "call failed");
			}

			/*Si el vagón está lleno*/
			if (strcmp(*result_2,"") == 0){

				printf("El vagón está completo.\n");
				break;
			}
			/*Si el vagón no está lleno*/
			else { 
				printf("El puesto fila %d columna %d está ocupado\nPuestos disponibles:\n%s\n", row, column, *result_2);
				printf("Número de fila: ");
				scanf ("%d", &row);
				printf("Número de columna: ");
				scanf ("%d", &column);
			}
		}
	}

	clnt_destroy(cl);
	free (row_column);
	exit (0);
}
