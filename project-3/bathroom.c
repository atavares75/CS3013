/*
 bathroom.c
 Authors: Alex Tavares, Leo Gonslaves
 Created On: 2/12/2018
 */
#include "bathroom.h"

extern Bathroom * bathroom;

/*
 * Enter the bathroom, but wait until vacant if occupied
 * by the opposite gender. Set state accordingly.
 */
void Enter(Gender g) {
	pthread_mutex_lock(&bathroom->lock);
	//checks if bathroom is occupied by persons of the opposite gender
	while (bathroom->population > 0 && bathroom->curGender != g) {
		printf("[%lu] Thread of gender %d waiting.\n",
				(unsigned long int) pthread_self(), (int) g);
		//signals queue_keeper thread that a queue has started
		bathroom->queueLength++;
		if (bathroom->queueLength == 1) {
			pthread_cond_broadcast(&bathroom->queueOccupied);
		}

		pthread_cond_wait(&bathroom->empty, &bathroom->lock);

		//signals queue that their is no queue
		bathroom->queueLength--;
		if (bathroom->queueLength == 0) {
			pthread_cond_broadcast(&bathroom->queueOccupied);
		}
	}
	bathroom->population++;
	printf("[%lu] Thread of gender %d entered bathroom.\n",
			(unsigned long int) pthread_self(), (int) g);
	if (bathroom->population == 1) {
		printf("   I was the first to enter. Bathroom gender is now %d.\n",
				(int) g);
		bathroom->curGender = g;
		pthread_cond_broadcast(&bathroom->vacant);
		//printf("-- cond signaled --.\n");
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
	printf("[%lu] Leaving bathroom... ", (unsigned long int) pthread_self());
	if (bathroom->population == 0) {
		printf("   Bathroom empty! Signaling...");
		pthread_cond_broadcast(&bathroom->empty);
		pthread_cond_broadcast(&bathroom->vacant);
	}
	printf("\n");
	pthread_mutex_unlock(&bathroom->lock);
}

/*
 * Initializes the bathroom. Should be only called by master thread.
 */
void Initialize() {
	bathroom = (Bathroom*) calloc(1, sizeof(Bathroom));

	bathroom->curGender = MALE;
	bathroom->population = 0;
	bathroom->queueLength = 0;
	pthread_mutex_init(&bathroom->lock, NULL);
	pthread_mutex_init(&bathroom->print_lock, NULL);
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
void Finalize() {

	//do this after we figure out how we are going to gather statistics
	printf("Number of usages: %d\n", bathroom->numUsages);
	printf("Total time bathroom was vacant in seconds: %f\n",
			1000000*bathroom->timeVacant);
	printf("Total time bathroom was occupied in seconds: %f\n",
			1000000*bathroom->timeOccupied);
	double avgQL = bathroom->totalQueueTimeOfPeople / bathroom->totalQueueTime;
	printf("Average Queue Length: %f\n", avgQL);
	double avgPIB = bathroom->totalOccupiedTimeOfPeople
			/ (1000000*bathroom->timeOccupied);
	printf("Average number of persons in the bathroom at the same time: %f\n",
			avgPIB);

	//TODO: figure out how to keep track of averaage queue length and average number of persons in bathroom
	free(bathroom);
}

/*
 *	Keeps track of time bathroom is vacant and time it is occupied
 */
void * Time_Keeper() {
	pthread_mutex_lock(&bathroom->lock);
	while (bathroom->flag) {

		if (bathroom->population == 0) {
			clock_t t;
			t = clock();
			pthread_cond_wait(&bathroom->vacant, &bathroom->lock);
			t = clock() - t;
			double vacantTime = ((double) t) / CLOCKS_PER_SEC;
			bathroom->timeVacant += vacantTime;
		} else {
			clock_t t;
			t = clock();
			pthread_cond_wait(&bathroom->vacant, &bathroom->lock);
			t = clock() - t;
			double occupiedTime = ((double) t) / CLOCKS_PER_SEC;
			bathroom->timeOccupied += occupiedTime;
		}

	}
	pthread_mutex_unlock(&bathroom->lock);

	return NULL;
}

void * Queue_Time_Keeper() {
	pthread_mutex_lock(&bathroom->lock);
	while (bathroom->flag) {

		if (bathroom->queueLength > 0) {
			clock_t t;
			t = clock();
			pthread_cond_wait(&bathroom->queueOccupied, &bathroom->lock);
			t = clock() - t;
			double queueTime = ((double) t) / CLOCKS_PER_SEC;
			bathroom->totalQueueTime += queueTime;
		} else {
			pthread_cond_wait(&bathroom->queueOccupied, &bathroom->lock);
		}

	}
	pthread_mutex_unlock(&bathroom->lock);

	return NULL;
}

