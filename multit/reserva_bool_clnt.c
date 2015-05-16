 /* 
 * reserva_bool_clnt.c
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Este archivo fue generado utilizando RPCGEN 
 */

#include <memory.h> /* for memset */
#include "reserva_bool.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
make_reservation_3(seat *argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, MAKE_RESERVATION,
		(xdrproc_t) xdr_seat, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
available_3(seat *argp, int *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, AVAILABLE,
		(xdrproc_t) xdr_seat, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
seats_3(void *argp, char **clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, SEATS,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_wrapstring, (caddr_t) clnt_res,
		TIMEOUT));
}
