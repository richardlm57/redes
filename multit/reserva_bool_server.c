/* 
 * reserva_bool_server.c
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * La plantilla de este archivo fue generado utilizando RPCGEN 
 */

#include "reserva_bool.h"

int train[10][4] = {{0}};

bool_t
make_reservation_3_svc(seat *myseat, int *result, struct svc_req *rqstp)
{
	bool_t retval;

	if (train[myseat->row - 1][myseat->column -1] == 0){
		train[myseat->row - 1][myseat->column - 1] = 1;
		retval = 1;
		*result = 1; 
	}
	else{
		retval = 1;
		*result = 0;
	}

	return retval;
}

bool_t
available_3_svc(seat *myseat, int *result, struct svc_req *rqstp)
{
	bool_t retval;

	if (train[myseat->row - 1][myseat->column -1] == 0){
		retval = 1;
		*result = 1;
	}
	else{
		retval = 1;
		*result = 0;
	}

	return retval;
}

bool_t
seats_3_svc(void *argp, char **result, struct svc_req *rqstp)
{
	bool_t retval;
	int i,j;
	char buffer[170];
	char temp[4];
	strcpy(buffer,"");

	printf("%s\n",  "HOLA");
	memset(*result,' ',170);
	printf("%s\n", "hey");
	for (i = 0; i < 10; i++){
		for (j = 0; j < 4; j++){
			if (train[i][j] == 0){
				sprintf(temp, "%d %d\n", i + 1, j + 1);
				//printf("%s\n", temp);
				strcat(buffer,temp);
			}
		}
	}
	printf("%s\n",buffer);
	printf("%d\n", strlen(buffer));
	printf("%s\n", *result);
	strcpy(*result,buffer);
	retval = 1;
	return 1;
}

int
reserva_bool_prog_3_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	//xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
