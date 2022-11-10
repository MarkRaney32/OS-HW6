#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#include "threadlib.c"

void multiply(int *x, int *y){
	printf(1, "x: %d\ny: %d\n", *x, *y);
	printf(1, "Result: %d\n", *x * *y);
	exit();
}

void race_condition(int* x, int* y) {
	for(int i = 0; i < 100000; i++) {
		x = x + 1;
		x = x - 1;
		if(x != 0)
		{
			//lock_acquire(lock_t *lock);
			printf(1, "Race Condition Achieved: %d\n", x);
			//lock_release(lock_t *lock);
			exit();
		}
	}
	exit();
}

void nrace_condition(int* x, int* y) {
	for(int i = 0; i < 100000; i++) {
		//lock_acquire(lock_t *lock);
		x = x + 1;
		x = x - 1;
		//lock_release(lock_t *lock);
		if(x != 0)
		{
			//lock_acquire(lock_t *lock);
			printf(1, "NRace Condition Achieved: %d\n", x);
			//lock_release(lock_t *lock);
			exit();
		}
	}
	exit();
}

int main() {

	//lock_t *tempLock;
	//lock_init(lock_t *tempLock);

	int x = 11;
	int y = 10;
	int rc = 0;

	thread_create((void(*)(void*,void*))multiply, &x, &y);
	thread_join();

	thread_create((void(*)(void*,void*))race_condition, &rc, &y);
	thread_create((void(*)(void*,void*))race_condition, &rc, &y);
	thread_join();
	thread_join();
	printf(1, "Race Condition Results: %d\n", rc);

	exit();
}
