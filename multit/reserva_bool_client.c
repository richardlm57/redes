 /* 
 * reserva_bool_client.c
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * La plantilla de este archivo fue generado utilizando RPCGEN 
 */

#include "reserva_bool.h"


void reserva_bool_prog_3(char *host, int row, int column){

	CLIENT *clnt;
	enum clnt_stat retval_1;
	int result_1;
	seat  make_reservation_3_arg;
	enum clnt_stat retval_2;
	int result_2;
	seat  available_3_arg;
	enum clnt_stat retval_3;
	char *result_3;
	char *seats_3_arg;


#ifndef	DEBUG
	clnt = clnt_create (host, RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_3 = malloc(sizeof(char)*170);

	while (1){
		/* Verificación de un valor válido para el número de fila*/
		if (row> 10 || row < 1 ){
			printf ("Error: Número de fila inválido \n");
			exit (1);
		}

		/* Verificación de un valor válido para el número de columna*/
		else if (column > 4 || column < 1 ){
			printf ("Error: Número de columna inválido\n");
			exit (1);
		}

		make_reservation_3_arg.row = row;
		make_reservation_3_arg.column = column;

		retval_1 = make_reservation_3(&make_reservation_3_arg, &result_1, clnt);

		if (retval_1 != RPC_SUCCESS) {
			clnt_perror (clnt, "Llamada fallida");
		}
		else if (result_1 == 1){
			printf("El puesto fila %d columna %d ha sido reservado\n", make_reservation_3_arg.row, make_reservation_3_arg.column);
			break;
		}
		else {
			printf("%s\n", "OCUPADO");
			retval_3 = seats_3((void*)&seats_3_arg, &result_3, clnt);
			
			if (retval_3 != RPC_SUCCESS) {
				clnt_perror (clnt, "Llamada fallida");
			}
			if (strcmp(result_3,"") == 0){
				printf("El vagón está completo.\n");
			break;
			}
			/*Si el vagón no está lleno*/
			else { 
				printf("Puesto ocupado\nPuestos disponibles:\n%s\n", result_3);
				row = -1;
				column = -1; 
				while (!(row > 0 && row < 11 && column > 0 && column < 5)){
					printf("Número de fila: ");
					scanf ("%d", &row);
					printf("Número de columna: ");
					scanf ("%d", &column);
				}
			}	
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
	free(result_3);

#endif	 /* DEBUG */
}

int main (int argc, char *argv[]){
	char *host;
	int row, column;

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

	host = argv[1];
	row = atoi(argv[3]);
	column = atoi(argv[5]);

	reserva_bool_prog_3 (host, row, column);
	exit (0);
}
