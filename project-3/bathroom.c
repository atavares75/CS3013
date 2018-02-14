/*
  bathroom.c
  Authors: Alex Tavares, Leo Gonslaves
  Created On: 2/12/2018
*/
#include "bathroom.h"


extern Bathroom * const bathroom;


/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(Gender g) {
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
		pthread_cond_signal(&bathroom->vacant);
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
	bathroom->numUsages++;
	if (bathroom->population == 0) {
		pthread_cond_signal(&bathroom->vacant);
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

	bathroom->numUsages = 0;
	bathroom->timeVacant = 0;
	bathroom->timeOccupied = 0;
	pthread_cond_init(&bathroom->vacant, NULL);
	bathroom->flag = 1;
}

/*
 *	Finalizes the execution of the bathroom.
 */
void Finalize(){
	//do this after we figure out how we are going to gather statistics
	printf("Number of usages: %d\n", bathroom->numUsages);
	printf("Total time bathroom was vacant in seconds: %ld\n", bathroom->timeVacant);
	printf("Total time bathroom was occupied in seconds: %ld\n", bathroom->timeOccupied);
	//TODO: figure out how to keep track of averaage queue length and average number of persons in bathroom

}

/*
 *	Keeps track of time bathroom is vacant and time it is occupied
 */
void *Time_Keeper(){
	pthread_mutex_lock(&bathroom->lock);
	while(bathroom->flag){
		
		if(bathroom->population == 0){
			clock_t t;
			t = clock();
			pthread_cond_wait(&bathroom->vacant, &bathroom->lock);
			t = clock() - t;
			double vacantTime = ((double) t)/CLOCKS_PER_SEC;
			bathroom->timeVacant += vacantTime;
		} else{
			clock_t t;
			t = clock();
			pthread_cond_wait(&bathroom->vacant, &bathroom->lock);
			t = clock() - t;
			double occupiedTime = ((double) t)/CLOCKS_PER_SEC;
			bathroom->timeOccupied += occupiedTime;
		}
		
	}
	pthread_mutex_unlock(&bathroom->lock);

	return NULL;
}
