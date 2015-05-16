/* 
 * reserva_bool.h
 *
 * 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Este archivo fue generado utilizando RPCGEN 
 */

#ifndef _RESERVA_BOOL_H_RPCGEN
#define _RESERVA_BOOL_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct seat {
	int row;
	int column;
};
typedef struct seat seat;

#define RESERVA_BOOL_PROG 99
#define RESERVA_BOOL_VERS 3

#if defined(__STDC__) || defined(__cplusplus)
#define MAKE_RESERVATION 1
extern  enum clnt_stat make_reservation_3(seat *, int *, CLIENT *);
extern  bool_t make_reservation_3_svc(seat *, int *, struct svc_req *);
#define AVAILABLE 2
extern  enum clnt_stat available_3(seat *, int *, CLIENT *);
extern  bool_t available_3_svc(seat *, int *, struct svc_req *);
#define SEATS 3
extern  enum clnt_stat seats_3(void *, char **, CLIENT *);
extern  bool_t seats_3_svc(void *, char **, struct svc_req *);
extern int reserva_bool_prog_3_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MAKE_RESERVATION 1
extern  enum clnt_stat make_reservation_3();
extern  bool_t make_reservation_3_svc();
#define AVAILABLE 2
extern  enum clnt_stat available_3();
extern  bool_t available_3_svc();
#define SEATS 3
extern  enum clnt_stat seats_3();
extern  bool_t seats_3_svc();
extern int reserva_bool_prog_3_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_seat (XDR *, seat*);

#else /* K&R C */
extern bool_t xdr_seat ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RESERVA_BOOL_H_RPCGEN */