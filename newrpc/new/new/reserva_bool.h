/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RESERVA_BOOL_H_RPCGEN
#define _RESERVA_BOOL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define RESERVA_BOOL_PROG 99
#define RESERVA_BOOL_VERS 3

#if defined(__STDC__) || defined(__cplusplus)
#define MAKE_RESERVATION 1
extern  int * make_reservation_3(char **, CLIENT *);
extern  int * make_reservation_3_svc(char **, struct svc_req *);
#define AVAILABLE 2
extern  int * available_3(char **, CLIENT *);
extern  int * available_3_svc(char **, struct svc_req *);
extern int reserva_bool_prog_3_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MAKE_RESERVATION 1
extern  int * make_reservation_3();
extern  int * make_reservation_3_svc();
#define AVAILABLE 2
extern  int * available_3();
extern  int * available_3_svc();
extern int reserva_bool_prog_3_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RESERVA_BOOL_H_RPCGEN */
