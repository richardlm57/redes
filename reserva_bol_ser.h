/* 
 * reserva_bol_ser.h
 *
 * Richard Lares. 11-10508
 * Patricia Reinoso. 11-10851
 *
 * Archivo con las librerías que debe importar el servidor del sistema de reserva de boletos
 * para ofrecer el servicio
 *
 */

#ifndef libser
	#define libser 1
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <strings.h>

	#include <sys/types.h>
	#include <pthread.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>

	#include <stddef.h>
	#include <unistd.h>

/* Estructura para la función de hilos */
typedef struct{
	int speak;
	char *ip;
} param;

#endif