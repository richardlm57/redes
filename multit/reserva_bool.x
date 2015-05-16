/* 
 * reserva_bool.x 
 *
 * Autores: 
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Este archivo contiene la especificación de la 
 * funciones del servidor, será compilado por RPCGEN.
 */

struct seat {
	int row;
	int column;
};

program RESERVA_BOOL_PROG {
	version RESERVA_BOOL_VERS {
		int MAKE_RESERVATION(seat) = 1;
		int AVAILABLE(seat) = 2;
		string SEATS(void) =3;
	} = 3;	
} = 99;
