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

void race_condition(int* x, void* y) {
	for(int i = 0; i < 10000000; i++) {
		*x += 1;
		*x -= 1;
	}
	printf(1, "val: %d\n", *x);
	exit();
}

int main() {
	int x = 10;
	int y = 11;
	int rc = 0;

	thread_create((void(*)(void*,void*))multiply, &x, &y);
	thread_create((void(*)(void*,void*))race_condition, &rc, &y);
	thread_join();

	exit();
}
