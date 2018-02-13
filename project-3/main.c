/**
 * 	Main source file for bathroom multi-threaded simulation.
 *
 * 	Authors: L. Gonsalves, A. Tavares
 *
 */
#include "bathroom.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 5




/* Global, unchangable pointer to bathroom struct, to be initialized */
Bathroom * const bathroom;

int main(int argc, char **argv) {
	/* Variables */
	int nUsers;
	int avgLoops;
	long meanArrival;
	long meanStay;

	/* Argument checking */
	if (argc > MAX_ARGS) {
		printf("Number of arguments is invalid, please try again.\n");
		exit(1);
	} else {
		nUsers = atoi(argv[1]);
		avgLoops = atoi(argv[2]);
		meanArrival = atoi(argv[3]);
		meanStay = atoi(argv[4]);
	}

	// TODO: Define bathroom initialization here (master thread)
	Initialize();
	// TODO: Write code for thread initialization
	// TODO: Wait for threads to finish

	exit(0);
}


