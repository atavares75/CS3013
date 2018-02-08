/*
 * monitor.c
 *
 *  Created on: Feb 6, 2018
 *      Authors: L. Gonsalves, A. Tavares
 */
#include <pthread.h>


/*
 *  Note: Not really sure what to do with these methods, we'll figure it out.
 *
 *  TODO: Write a monitor using semaphores
 */



   int pthread_cond_init(pthread_cond_t * cond, const pthread_cond_attr *attr);
   /*	Initialization of cond. Usually attr is initialized to
        pthread_condattr_default */

   int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
   /*	When this command is executed the executing thread goes to sleep
		on cond and simultaneously mutex is unlocked, thus allowing another
		thread to execute past a lock on mutex. When a thread is released
		from waiting on a condition variable, its mutex is implicitly locked. */

   int pthread_cond_signal(pthread_cond_t * cond);
   /*	This command is null when no thread is asleep on cond. Otherwise
		a thread is released from cond. */

