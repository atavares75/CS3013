/**
 * 	Main source file for bathroom multi-threaded simulation.
 *
 * 	Authors: L. Gonsalves, A. Tavares
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "person.h"
#include "bathroom.h"

#define MAX_ARGS 6

/* Global, unchangable pointer to bathroom struct, to be initialized */
Bathroom * bathroom;

int main(int argc, char **argv) {
	/* Variables */
	int nUsers;
	int avgLoops;
	double meanArrival;
	double meanStay;
	int seed;

	/* Argument checking */
	if (argc > MAX_ARGS || argc < 5) {
		printf("Number of arguments is invalid, please try again.\n");
		printf("  Syntax -- ./bathroomSim nUsers avgLoops avgArrival averageStayTime (opt)seed\n");
		exit(1);
	} else {
		nUsers = atoi(argv[1]);
		avgLoops = atoi(argv[2]);
		meanArrival = atof(argv[3]);
		meanStay = atof(argv[4]);

		if (argc == MAX_ARGS) {
			seed = atoi(argv[5]);
			srand48(seed);
		}
		else
			srand48(time(NULL));
	}

	Person personArray[nUsers];

	
	Initialize();

	pthread_t timerThread;

	int r_code;
	if((r_code = pthread_create(&timerThread, NULL, Time_Keeper, NULL)) != 0){
			printf("Error creating thread\n");
			exit(r_code);
		}	

	/* Initialize a thread for each person */
	for (int p = 0; p < nUsers; p++){
		Gender g;
		genGender(&g);

		int loops;
		genLoops(&loops, avgLoops);

		personArray[p].gender = g;
		personArray[p].maximumWaitTime = 0;
		personArray[p].minimumWaitTime = INFINITY;
		personArray[p].totalStayTime = 0;
		personArray[p].totalWaitTime = 0;
		personArray[p].loopCount = loops;
		personArray[p].meanArrivalTime = meanArrival;
		personArray[p].meanStayTime = meanStay;

		int error_code;
		if((error_code = pthread_create(&personArray[p].thread, NULL, Individual, &personArray[p]) != 0)){
			printf("Error creating thread\n");
			exit(error_code);
		}

	}


	for(int j = 0; j < nUsers; j++){
		pthread_join(personArray[j].thread, NULL);
	}


	//ends timer thread
	pthread_mutex_lock(&bathroom->lock);
	bathroom->flag = 0;
	//makes sure time keeper isn't stuck waiting for condition
	pthread_cond_signal(&bathroom->vacant);
	pthread_mutex_unlock(&bathroom->lock);
	pthread_join(timerThread, NULL);


	Finalize();

	exit(0);
}


