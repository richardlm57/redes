/* 
 * reserva_bool.x 
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
