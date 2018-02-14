/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonslves, A. Tavares
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BATHROOM_H_
#define BATHROOM_H_

typedef enum Gender {
	MALE, FEMALE
} Gender;

typedef struct Bathroom_Object {
	Gender curGender;
	int population;
	pthread_mutex_t lock;
	int queueLength;
	pthread_cond_t empty;

	int numUsages;
	long timeVacant;
	long timeOccupied;
	pthread_cond_t vacant;
	int flag;
} Bathroom;

/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(Gender g);

/*
 * Leave bathroom. Set state to "vacant" if this thread is the
 * last one out.
 */
void Leave();

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize();

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize();


/*
 *	Keeps track of time bathroom is vacant and time it is occupied
 */
void *Time_Keeper();


#endif /* BATHROOM_H_ */
