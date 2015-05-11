#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <rpc/rpc.h>
#include "msg.h"

int train[10][4]

int * disponible_1 (int i, int j) {

	static int result;
	int * i;
	int * j;

	if (train[i-1][j-1] == 0) {
		train[i-1][j-1] = 1;
		result = 1;
		return (&result); 
	}	 
	else {
		result = 0;
		return (&result);
	}
}