/*
  bathroom.c
  Authors: Alex Tavares, Leo Gonslaves
  Created On: 2/12/2018
*/
#include "bathroom.h"

typedef struct Bathroom_Object {
	gender curGender;
	int population;
	pthread_mutex_t lock;
	int queueLength;
	pthread_cond_t empty;
} Bathroom;


extern Bathroom * const bathroom;


/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(gender g) {
	pthread_mutex_lock(&bathroom->lock);
	//checks if bathroom is occupied by persons of the opposite gender
	while (bathroom->population != 0 && bathroom->curGender != g) {
		bathroom->queueLength++;
		pthread_cond_wait(&bathroom->empty, &bathroom->lock);
		bathroom->queueLength--;
	}
	bathroom->population++;
	if (bathroom->population == 1) {
		bathroom->curGender = g;
	}
	pthread_mutex_unlock(&bathroom->lock);


}



/*
 * Leave bathroom. Set state to "vacant" if this thread is the
 * last one out.
 */
void Leave() {
	pthread_mutex_lock(&bathroom->lock);
	bathroom->population--;
	if (bathroom->population == 0) {
		pthread_cond_broadcast(&bathroom->empty);
	}
	pthread_mutex_unlock(&bathroom->lock);
}

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize() {
	bathroom->curGender = MALE;
	bathroom->population = 0;
	bathroom->queueLength = 0;
	pthread_mutex_init(&bathroom->lock, NULL);
	pthread_cond_init(&bathroom->empty, NULL);
}

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize(){

}