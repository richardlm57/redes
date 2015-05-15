/* 
 * reserva_bol.x 
 */

program RESERVA_BOL_PROG {
	version RESERVA_BOL_VERS {
		int MAKE_RESERVATION(string) = 1;
		int IS_AVAILABLE(string) = 1;
	} = 2;	
} = 99;
