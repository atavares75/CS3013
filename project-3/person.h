/*
 * person.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonsalves, A. Tavares
 */

#ifndef PERSON_H_
#define PERSON_H_

#include "bathroom.h"
#include </usr/include/pthread.h>
#include <math.h>


struct Person_Object {
	pthread_t thread;
	Gender gender;
	double totalWaitTime;
	double totalStayTime;
	double minimumWaitTime;
	double maximumWaitTime;
	int loopCount;
	double meanArrivalTime;
	double meanStayTime;
};

typedef struct Person_Object Person;


// generates a random stay/wait time
void genTime(double* time, double mean);
void genLoops(int* avgLoops, int mean);
void genGender(Gender* gender);

// implementation of thread
void *Individual(void* p);

#endif /* PERSON_H_ */
