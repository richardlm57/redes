/* 
 * reserva_svc.c
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Este archivo fue generado utilizando RPCGEN 
 */

#include "reserva_bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
reserva_bool_prog_3(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		seat make_reservation_3_arg;
		seat available_3_arg;
	} argument;
	union {
		int make_reservation_3_res;
		int available_3_res;
		char *seats_3_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case MAKE_RESERVATION:
		_xdr_argument = (xdrproc_t) xdr_seat;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))make_reservation_3_svc;
		break;

	case AVAILABLE:
		_xdr_argument = (xdrproc_t) xdr_seat;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))available_3_svc;
		break;

	case SEATS:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (bool_t (*) (char *, void *,  struct svc_req *))seats_3_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "No se pudo liberar los argumentos");
		exit (1);
	}
	if (!reserva_bool_prog_3_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "No se puedo liberar las respuestas");

	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (RESERVA_BOOL_PROG, RESERVA_BOOL_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "No se puede crear el servicio upd");
		exit(1);
	}
	if (!svc_register(transp, RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, reserva_bool_prog_3, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "No se pudo registrar (RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "No se puede crear el servicio tcp.");
		exit(1);
	}
	if (!svc_register(transp, RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, reserva_bool_prog_3, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "No se pudo registrar (RESERVA_BOOL_PROG, RESERVA_BOOL_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
