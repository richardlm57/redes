/* 
 * reserva_bool_xdr.c
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Este archivo fue generado utilizando RPCGEN 
 */

#include "reserva_bool.h"

bool_t
xdr_seat (XDR *xdrs, seat *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->row))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->column))
		 return FALSE;
	return TRUE;
}
