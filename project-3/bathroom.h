/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonslves, A. Tavares
 */

#ifndef BATHROOM_H_
#define BATHROOM_H_

#include </usr/include/pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Gender {
	MALE, FEMALE
} Gender;

typedef struct Bathroom_Object {
	Gender curGender;
	int population;
	pthread_mutex_t lock;
	pthread_mutex_t print_lock;
	int queueLength;
	pthread_cond_t empty;

	int numUsages;
	double timeVacant;
	double timeOccupied;
	pthread_cond_t vacant;
	pthread_cond_t queueOccupied;
	int flag;
	double totalQueueTime;
	double totalQueueTimeOfPeople;
	double totalOccupiedTimeOfPeople;

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
void * Time_Keeper();

/*
 * keeps track of amount of time that the queue is non-empty
 */
void * Queue_Time_Keeper();


#endif /* BATHROOM_H_ */
