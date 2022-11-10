/*
 *
 * ADDED BY MARK AND HENRY
 *
 */


#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#include "threadlib.c"
//#include "threadlib.h"

int counter = 0;
struct __lock_t lock;

void multiply(int *x, int *y){
	printf(1, "\nx: %d\ny: %d\n", *x, *y);
	printf(1, "x * y =  %d\n", *x * *y);
	exit();
}

void race_condition(int* x, int* y) {
	for(int i = 0; i < *x; i++){
		counter += 1;
		if(i % *y == 0){
			//printf(1, "Current Val: %d\n", counter);
			sleep(0.5);
		}
	}
	exit();
}

void race_condition_withlock(int *x, int *y) {
	lock_acquire(&lock);
	for(int i = 0; i < *x; i++){
		//lock_acquire(&lock);
		counter += 1;
		//lock_release(&lock);
		if(i % *y == 0){
			//printf(1, "Sleeping... {%d}\n", counter);
			sleep(0.5);
			//printf(1, "Waking up! {%d}\n", counter);
		}
	}
	lock_release(&lock);
	exit();
}

void test_lock(int* dummy1, int* dummy2) {
	lock_acquire(&lock);
	lock_release(&lock);
	//printf(1, "Lock test: successful!\n");
	exit();
}

int main() {

	lock_init(&lock);

	int loops = 100000;
	int sleep_divisor = 10000;
	int rc;

	// Just checking that thread_create works
	rc = thread_create((void(*)(void*,void*))multiply, &loops, &sleep_divisor);
	thread_join();
	printf(1, "\nthread pid: %d\n", rc);

	// Just checking that locking works at all
	rc = thread_create((void(*)(void*,void*))test_lock, &loops, &sleep_divisor);
	rc = thread_create((void(*)(void*,void*))test_lock, &loops, &sleep_divisor);
	thread_join();
	thread_join();
	printf(1, "\nLock test successful!\n");

	// Checking that race condition does what we expect w/o locks
	rc = thread_create((void(*)(void*,void*))race_condition, &loops, &sleep_divisor);
	rc = thread_create((void(*)(void*,void*))race_condition, &loops, &sleep_divisor);
	thread_join();
	thread_join();
	printf(1, "\n          Race Condition Results: %d\n", counter);

	// Checking same race condition, now with lock in place.
	counter = 0;
	rc = thread_create((void(*)(void*,void*))race_condition_withlock, &loops, &sleep_divisor);
	rc = thread_create((void(*)(void*,void*))race_condition_withlock, &loops, &sleep_divisor);
	thread_join();
	thread_join();
	printf(1, "\nRace Condition with lock results: %d\n", counter);

	exit();

}
