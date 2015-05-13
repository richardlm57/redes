/* 
 * reserva_bol.x 
 */

program RESERVA_BOL_PROG {
	version RESERVA_BOL_VERS {
		int IS_AVAILABLE(string) = 1;
		string SEATS(void) = 2;
	} = 2;	
} = 99;
