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



/* Individual Thread Routine */
void *Individual(void * p){
	Person *prsn = (Person *)p;

	for(int i = 0; i < prsn->loopCount; i++){

		long arrivalTime;
		genTime(&arrivalTime, prsn->meanArrivalTime);

		sleep(arrivalTime);

		clock_t t;
		t = clock();
		Enter(prsn->gender);
		t = clock() - t;
		double timeWaiting = ((double) t)/CLOCKS_PER_SEC;

		//TODO: figure out where to store waitTime

		long stayTime;
		genTime(&stayTime, prsn->meanStayTime);

		sleep(stayTime);

		Leave();
	}



}

/* Helpers */
void genTime(long* time, long mean){
	//TODO: define random time generation, check project instructions for details on how to do this
	long t = 0;
	long stdev = mean/2;
	while(t <= 0){

	}
	
}
void genLoops(int* avgLoops){
	//TODO: define random number of loops generation

}
void genGender(Gender *gender){
	int num = rand();

	if(num%2 == 0){
		gender = MALE;
	} else{
		gender = FEMALE;
	}

}
