/* 
 * reserva_bool.x 
 */

program RESERVA_BOOL_PROG {
	version RESERVA_BOOL_VERS {
		int MAKE_RESERVATION(string) = 1;
		int AVAILABLE(string) = 2;
	} = 3;	
} = 99;
