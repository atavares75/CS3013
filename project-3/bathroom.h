/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonslves
 */

#include <semaphore.h>

#ifndef BATHROOM_H_
#define BATHROOM_H_



/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(enum gender g);


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




#endif /* BATHROOM_H_ */
