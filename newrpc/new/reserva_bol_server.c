/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "reserva_bol.h"

int train[10][4] = {{0}};

int * is_available_2_svc(char **row_column, struct svc_req *rqstp) {

	static int  result;

	char *token;
	int row, column;

	token = strtok(*row_column, " ");
	row = atoi(token);
	token = strtok(NULL, " ");
	column = atoi(token);

	if (train[row - 1][column -1] == 0){
		train[row - 1][column - 1] = 1;
		result = 1;
		return (&result);
	}
	else{
		result = 0;
		return &result;
	}
}

char ** seats_2_svc(void *argp, struct svc_req *rqstp){

	static char *result;
	char buffer [170]; 
	char temp[1];
	int i, j;

	strcpy(buffer,"");
	for (i = 0; i < 10; i++){
		for (j = 0; j < 4; j++){
			if (train[i][j] == 0){
				sprintf(temp, "%d", i+1);
				strcat(buffer, temp);
				strcat(buffer, " ");
				sprintf(temp, "%d", j+1);
				strcat(buffer, temp);
				strcat(buffer, "\n");
			}
		}
	}
	strcpy(result,buffer);
	return &result;
}