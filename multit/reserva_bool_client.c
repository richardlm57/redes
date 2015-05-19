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

	CLIENT *clnt;					// Cliente
	enum clnt_stat retval_1;		// retorno de la función make_reservation
	int result_1;					// indica si el puesto está disponible o no
	seat  make_reservation_3_arg;	// asiento a verificar si está disponible
	enum clnt_stat retval_3;		// retorno de la función seats
	char *result_3;					// lista de puestos disponibles
	char *seats_3_arg;				// argumento del procedimiento  seats
	int i;							// iterador


#ifndef	DEBUG

	for (i = 0; i < 3; i++){
	
		clnt = clnt_create (host, RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, "tcp");
		
		if (clnt == NULL)  {
			clnt_pcreateerror (host);
		}
		else{
			break;
		}
		if (i == 2){
			exit (1);
		}
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

		if (result_1 == 1){
			printf("El puesto fila %d columna %d ha sido reservado\n", 
				make_reservation_3_arg.row, make_reservation_3_arg.column);
			break;
		}
		else if (result_1 == 0) {
				
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
					if (row> 10 || row < 1 ){
						printf ("Error: Número de fila inválido \n");
					}

					/* Verificación de valor válido para el número de columna*/
					if (column > 4 || column < 1 ){
						printf ("Error: Número de columna inválido\n");
					}
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
	char *host;			// direccion ip del servidor
	int row, column;	// fila y columna del puesto

	/* Verificación de los argumentos de entrada*/ 
	if ((argc != 6) ||(strcmp(argv[2],"-f") != 0)  || 
		(strcmp(argv[4],"-c") != 0)){
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
