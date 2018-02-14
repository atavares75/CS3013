/*
 * person.c
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonsalves
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

		long arrivalTime;
		genTime(&arrivalTime, prsn->meanArrivalTime);

		sleep(arrivalTime);

		clock_t t;
		t = clock();
		Enter(prsn->gender);
		t = clock() - t;
		double timeWaiting = ((double) t)/CLOCKS_PER_SEC;

		
		if(prsn->maximumWaitTime < timeWaiting){
			prsn->maximumWaitTime = (int)timeWaiting;
		}
		if(prsn->minimumWaitTime > timeWaiting){
			prsn->minimumWaitTime = (int)timeWaiting;
		}
		prsn->totalWaitTime += timeWaiting;

		long stayTime;
		genTime(&stayTime, prsn->meanStayTime);
		prsn->totalStayTime += stayTime;

		sleep(stayTime);

		Leave();
	}
	pthread_t tid = *(prsn->thread);
	printf("Thread ID: %lu\n", (unsigned long int)tid);

	if(prsn->gender == MALE){
		printf("Gender: Male\n");
	} else{
		printf("Gender: Female\n");
	}

	printf("Number of loops: %d", (int)prsn->loopCount);

	int averageTimeSpentInQueue = (int)prsn->totalWaitTime/(int)prsn->loopCount;
	printf("Minimum time spent in the queue in seconds: %d", (int)prsn->minimumWaitTime);
	printf("Average time spent in the queue in seconds: %d", averageTimeSpentInQueue);
	printf("Maximum time spent in the queue in seconds: %d", (int)prsn->maximumWaitTime);

	return NULL;
}


/* Helpers */
void genTime(long* time, long mean){
	//TODO: define random time generation, check project instructions for details on how to do this
	float stdev = 2.78;

	float a = drand48();
	float b = drand48();
	
	int z = sqrt(-2 * log(a)) * cos(2 * M_PI * b);

	z = (stdev * z) + mean;

	*time = z;
}

void genLoops(int* loops, int mean){
	//TODO: define random number of loops generation
	float stdev = 2.78;

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
	} else{
		*gender = FEMALE;
	}

}
