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

struct Person {
	pthread_t *thread;
	Gender gender;
	unsigned long totalWaitTime;
	unsigned long totalStayTime;
	unsigned int minimumWaitTime;
	unsigned int maximumWaitTime;
	unsigned int loopCount;
};

// generates a random stay/wait time
void genTime(long* time);
void genLoops(int* avgLoops);
void genGender(Gender* gender);

// implementation of thread
void Individual(struct Person* p);

#endif /* PERSON_H_ */
