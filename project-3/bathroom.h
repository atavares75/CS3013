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

enum state {
	MALE, FEMALE
};

typedef struct Bathroom_Object {
	enum state curGender;
	int population;
	//sem_t bathroom_lock;
	mutex lock;
	long occupiedTime;
	long vacantTime;
	int avgQueueLength;
	int avgPopulation;
	sem_t men_waiting_lock;
	sem_t women_waiting_lock;
	int men_waiting;
	int women_waiting;
} Bathroom;


/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(enum gender g) {
	sem_wait(&bathroom->lock);
	//checks if bathroom is occupied by persons of the opposite gender
	if (bathroom->population != 0 && bathroom->curGender != g) {
		if (g == MALE) {
			bathroom->men_waiting++;
			sem_post(&bathroom->lock);
			sem_wait(&bathroom->men_waiting_lock);
		} else {
			bathroom->women_waiting++;
			sem_post(&bathroom->lock);
			sem_wait(&bathroom->women_waiting_lock);
		}

	} else {
		bathroom->population++;
		if (bathroom->population == 1) {
			bathroom->curGender = g;
		}
		sem_post(&bathroom->lock);
	}

}



/*
 * Leave bathroom. Set state to "vacant" if this thread is the
 * last one out.
 */
void Leave() {
	sem_wait(&bathroom->lock);
	bathroom->population--;
	if (bathroom->population == 0) {
		bathroom->curGender = VACANT;
		if (bathroom->women_waiting > 0) {
			while (bathroom->women_waiting > 0) {
				bathroom->women_waiting--;
				bathroom->population++;
				sem_post(&bathroom->women_waiting_lock);
			}
		} else if (bathroom->men_waiting > 0) {
			while (bathroom->women_waiting > 0) {
				bathroom->men_waiting--;
				bathroom->population++;
				sem_post(&bathroom->men_waiting_lock);
			}
		}
	}
	sem_post(&bathroom->lock);
}

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize() {
	bathroom->curGender = VACANT;
	bathroom->population = 0;
	bathroom->men_waiting = 0;
	bathroom->women_waiting = 0;
	if (sem_init(&bathroom->lock, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(&bathroom->men_waiting_lock, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(&bathroom->women_waiting_lock, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}
	bathroom->occupiedTime = 0;
	bathroom->vacantTime = 0;
	bathroom->avgQueueLength = 0;
	bathroom->avgPopulation = 0;
}

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize();
#endif /* BATHROOM_H_ */
