/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonslves
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BATHROOM_H_
#define BATHROOM_H_

typedef enum Gender {
	MALE, FEMALE
} g;

typedef struct Bathroom_Object {
	enum gender curGender;
	int population;
	pthread_mutex_lock lock;
	int queueLength;
	pthread_cond_t empty;
} Bathroom;


extern Bathroom * const bathroom;


/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(enum gender g) {
	pthread_mutex_lock(bathroom->lock);
	//checks if bathroom is occupied by persons of the opposite gender
	while (bathroom->population != 0 && bathroom->curGender != g) {
		
		pthread_cond_wait(bathroom->empty, bathroom->lock);
	}
	bathroom->population++;
	if (bathroom->population == 1) {
		bathroom->curGender = g;
	}
	pthread_mutex_unlock();


}



/*
 * Leave bathroom. Set state to "vacant" if this thread is the
 * last one out.
 */
void Leave() {
	pthread_mutex_lock(bathroom->lock);
	bathroom->population--;
	if (bathroom->population == 0) {
		bathroom->curGender = 0;
		pthread_cond_broadcast(bathroom->empty);
	}
	pthread_mutex_unlock(bathroom->lock);
}

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize() {
	bathroom->curGender = NULL;
	bathroom->population = 0;
	bathroom->waiting = 0;
	bathroom->queueLength = 0;
	bathroom->lock = PTHREAD_MUTEX_INITIALIZER;
	bathroom->empty = PTHREAD_COND_INITIALIZER;
}

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize();
#endif /* BATHROOM_H_ */
