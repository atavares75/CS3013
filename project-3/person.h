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
	enum gender gender;
	int meanWaitTime;
	int meanStayTime;
	int loopCount;
};

// generates a random stay/wait time
void genTime(int* time);
void genLoops(int* avgLoops);
void genGender(enum gender* gender);

// implementation of thread
void Individual(struct Person);


#endif /* PERSON_H_ */
