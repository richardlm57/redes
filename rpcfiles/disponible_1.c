#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <rpc/rpc.h>
#include "disp.h"

int train[10][4];

int * disponible_1 (i) 
	int * i;
	{
	int fila;
	fila = *i;
	static int result;
	int * j;

	if (train[fila - 1][fila - 1] == 0) {
		train[fila - 1][fila - 1] = 1;
		result = 1;
		return (&result); 
	}	 
	else {
		result = 0;
		return (&result);
	}

}