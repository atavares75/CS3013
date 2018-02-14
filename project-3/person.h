/*
 * person.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonsalves
 */
#include "bathroom.h"
#include </usr/include/pthread.h>

#ifndef PERSON_H_
#define PERSON_H_

typedef struct Person_Object {
	pthread_t *thread;
	Gender gender;
	double totalWaitTime;
	unsigned long totalStayTime;
	unsigned int minimumWaitTime;
	unsigned int maximumWaitTime;
	unsigned int loopCount;
	unsigned long meanArrivalTime;
	unsigned long meanStayTime;
} Person;

// generates a random stay/wait time
void genTime(long* time, long mean);
void genLoops(int* avgLoops, int mean);
void genGender(Gender* gender);

// implementation of thread
void *Individual(void* p);

#endif /* PERSON_H_ */
