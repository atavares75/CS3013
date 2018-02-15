/*
 * person.c
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonsalves, A. Tavares
 *
 *
 *     	Contains source file for generating random amounts of time,
 *     	loop count, gender, arrival time, and stay time.
 */

#include "bathroom.h"
#include "person.h"
#include <unistd.h>
#include <time.h>
#include <math.h>


/* Individual Thread Routine */
void* Individual(void * p){
	Person *prsn = (Person *)p;

	for(int i = 0; i < prsn->loopCount; i++){

		double arrivalTime;
		genTime(&arrivalTime, prsn->meanArrivalTime);

		if(usleep((unsigned int)arrivalTime) != 0){
			printf("Error with usleep for arrival time\n");
		}

		clock_t t;
		t = clock();
		Enter(prsn->gender);
		t = clock() - t;
		double timeWaiting = ((double) t)/CLOCKS_PER_SEC;

		
		if(prsn->maximumWaitTime < timeWaiting){
			prsn->maximumWaitTime = timeWaiting;
		}
		if(prsn->minimumWaitTime > timeWaiting && timeWaiting > 0){
			prsn->minimumWaitTime = timeWaiting;
		}
		prsn->totalWaitTime += timeWaiting;

		double stayTime;
		genTime(&stayTime, prsn->meanStayTime);
		prsn->totalStayTime += stayTime;

		if(usleep((unsigned int)stayTime) != 0){
			printf("Error with usleep for stay time\n");
		}
		

		Leave();
	}
	pthread_t tid = prsn->thread;
	printf("Thread ID: %lu\n", (unsigned long int)tid);

	if(prsn->gender == MALE){
		printf("Gender: Male\n");
	} else{
		printf("Gender: Female\n");
	}

	printf("Number of loops: %d\n", prsn->loopCount);

	double averageTimeSpentInQueue = prsn->totalWaitTime/prsn->loopCount;
	printf("Minimum time spent in the queue in seconds: %f\n", prsn->minimumWaitTime);
	printf("Average time spent in the queue in seconds: %f\n", averageTimeSpentInQueue);
	printf("Maximum time spent in the queue in seconds: %f\n\n", prsn->maximumWaitTime);

	return NULL;
}


/* Helpers */
void genTime(double* time, double mean){
	//TODO: define random time generation, check project instructions for details on how to do this
	float stdev = mean/2;

	float a = drand48();
	float b = drand48();
	
	double z = sqrt(-2 * log(a)) * cos(2 * M_PI * b);

	z = (stdev * z) + mean;

	*time = z;
}

void genLoops(int* loops, int mean){
	//TODO: define random number of loops generation
	float stdev = mean/2;

	float a = drand48();
	float b = drand48();

	int z = sqrt(-2 * log(a)) * cos(2 * M_PI * b);

	z = (stdev * z) + mean;

	*loops = z;
}


void genGender(Gender *gender){
	int num = rand();

	if(num%2 == 0){
		*gender = MALE;
	}
	else
		*gender = FEMALE;

}
