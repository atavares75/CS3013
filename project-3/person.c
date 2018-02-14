/*
 * person.c
 *
 *  Created on: Feb 7, 2018
 *      Author: L. Gonsalves
 *
 *
 *     	Contains source file for generating random amounts of time,
 *     	loop count, gender, arrival time, and stay time.
 */

#include "bathroom.h"
#include "person.h"
#include <unistd.h>
#include <time.h>

#define RAND_MAX 99

/* Individual Thread Routine */
void *Individual(void * p){
	Person *prsn = (Person *)p;

	for(int i = 0; i < prsn->loopCount; i++){

		long waitTime;
		genTime(&waitTime);

		sleep(waitTime);

		clock_t t;
		t = clock();
		Enter(prsn->gender);
		t = clock() - t;
		double timeWaiting = ((double) t)/CLOCKS_PER_SEC;

		long stayTime;
		genTime(stayTime);

		sleep(stayTime);

		Leave();
	}



}

/* Helpers */
void genTime(long* time){
	//TODO: define random time generation
	
}
void genLoops(int* avgLoops){
	//TODO: define random number of loops generation

}
void genGender(Gender *gender){
	//TODO: define random gender generator
	int num = rand();

	if(num%2 == 0){
		gender = MALE;
	} else{
		gender = FEMALE;
	}

}
