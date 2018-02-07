/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonslves
 */

#ifndef BATHROOM_H_
#define BATHROOM_H_

enum gender {MALE, FEMALE};

struct Bathroom {
	enum gender curGender;
    int population;
};

struct BathroomData {
	long occupiedTime;
	long vacantTime;
	int avgQueueLength;
	int avgPopulation;
};

/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(enum gender g);

/*
 * Leave bathroom. Set state to "vacant" if this thread is the
 * last one out.
 */
void Leave(void);

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize(void);

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize(void);

#endif /* BATHROOM_H_ */
