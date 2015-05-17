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
 #define SPLIT_S_ADDR_INTO_BYTES( \
    s_addr) \
    ((s_addr) >> 24) & 0xFF, \
    ((s_addr) >> 16) & 0xFF, \
    ((s_addr) >>  8) & 0xFF, \
    ((s_addr)      ) & 0xFF

int train[10][4] = {{0}};

bool_t
make_reservation_3_svc(seat *myseat, int *result, struct svc_req *rqstp)
{
	bool_t retval;
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	char *token;

	time( &rawtime );

	info = localtime( &rawtime );
	strcpy(buffer,asctime(info));
	token = strtok(buffer, "\n");

	FILE *f = fopen("log-server", "a");
	if (f == NULL){

	    printf("Error al abrir el archivo\n");
	    retval = 0;
	}
	
	if (train[myseat->row - 1][myseat->column -1] == 0){
		train[myseat->row - 1][myseat->column - 1] = 1;
		
		fprintf(f,"[%s] [error] [cliente %hu.%hu.%hu.%hu]: Puesto fila %d, columna %d reservado.\n", 
	   	token, SPLIT_S_ADDR_INTO_BYTES(ntohl(rqstp->rq_xprt->xp_raddr.sin_addr.s_addr)),
	   	myseat->row, myseat->column);

		retval = 1;
		*result = 1; 
	}
	else{

		fprintf(f,"[%s] [error] [cliente %hu.%hu.%hu.%hu]: Puesto fila %d, columna %d ocupado.\n", 
	   	token, SPLIT_S_ADDR_INTO_BYTES(ntohl(rqstp->rq_xprt->xp_raddr.sin_addr.s_addr)),
	   	myseat->row, myseat->column);

		retval = 1;
		*result = 0;
	}
	
	fclose(f);
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

	time_t rawtime;
	struct tm *info;
	char buffer2[80];
	char *token;

	time( &rawtime );

	info = localtime( &rawtime );
	strcpy(buffer2,asctime(info));
	token = strtok(buffer2, "\n");

	FILE *f = fopen("log-server", "a");
	if (f == NULL){

	    printf("Error al abrir el archivo\n");
	    retval = 0;
	}

	memset(*result,' ',170);

	for (i = 0; i < 10; i++){
		for (j = 0; j < 4; j++){
			if (train[i][j] == 0){
				sprintf(temp, "%d %d\n", i + 1, j + 1);
				//printf("%s\n", temp);
				strcat(buffer,temp);
			}
		}
	}
	strcpy(*result,buffer);
	retval = 1;

	if (strcmp(*result,"") == 0){
		fprintf(f,"[%s] [error] [cliente %hu.%hu.%hu.%hu]: Vagón completo.\n", 
		   	token, SPLIT_S_ADDR_INTO_BYTES(ntohl(rqstp->rq_xprt->xp_raddr.sin_addr.s_addr)));
	}
	else{
		fprintf(f,"[%s] [error] [cliente %hu.%hu.%hu.%hu]: Lista de puestos disponibles.\n", 
		   	token, SPLIT_S_ADDR_INTO_BYTES(ntohl(rqstp->rq_xprt->xp_raddr.sin_addr.s_addr)));

	}
	fclose(f);
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
