/**
 * 	Main source file for bathroom multi-threaded simulation.
 *
 * 	Authors: L. Gonsalves, A. Tavares
 *
 */
#include "bathroom.h"
#include <stdio.h>
#include <stdlib.h>
#include "person.h"

#define MAX_ARGS 6




/* Global, unchangable pointer to bathroom struct, to be initialized */
Bathroom * const bathroom;

int main(int argc, char **argv) {
	/* Variables */
	int nUsers;
	int avgLoops;
	long meanArrival;
	long meanStay;
	int seed;

	/* Argument checking */
	if (argc > MAX_ARGS) {
		printf("Number of arguments is invalid, please try again.\n");
		exit(1);
	} else {
		nUsers = atoi(argv[1]);
		avgLoops = atoi(argv[2]);
		meanArrival = atoi(argv[3]);
		meanStay = atoi(argv[4]);

		if (argc == MAX_ARGS) {
			seed = atoi(argv[5]);
		}
	}

	Person personArray[nUsers];

	// TODO: Define bathroom initialization here (master thread)
	Initialize();

	// TODO: Write code for thread initialization
	/* Initialize a thread for each person */
	for (int p = 0; p < nUsers; p++){
		Gender g;
		genGender(&g);

		int loops;
		genLoops(&loops);

		long waitTime;
		genTime(&waitTime);

		personArray[p].gender = g;
		personArray[p].maximumWaitTime = 0;
		personArray[p].minimumWaitTime = ~0;
		personArray[p].totalStayTime = 0;
		personArray[p].totalWaitTime = 0;
		personArray[p].loopCount = loops;
		personArray[p].meanArrivalTime = meanArrival;
		personArray[p].meanStayTime = meanStay;

		int r_code;
		pthread_t person;
		if((r_code = pthread_create(&person, NULL, Individual, &personArray[p])) != 0){
			printf("Error creating thread");
			exit(r_code);
		}

	}

	// TODO: Wait for threads to finish

	Finalize();

	exit(0);
}


