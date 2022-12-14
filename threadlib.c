/*
 * ADDED BY MARK AND HENRY
 *
 * */


#include "user.h"
#include "threadlib.h"
#define PGSIZE          4096

// Creating and joining threads

int thread_create(void (*fcn)(void *, void *), void *arg1, void *arg2) {
  void* stack = malloc(2*PGSIZE);
	int result = clone(fcn, arg1, arg2, stack);
  return result;
}

int thread_join() {
  void** stack = (void**) malloc(2*PGSIZE);
  int result = join(stack);
  return result;
}

// Lock nonsense

void lock_init(struct __lock_t *lock) {
  lock->ticket = 0;
  lock->turn = 0;
}

void lock_acquire(struct __lock_t *lock) {
  int myturn = FetchAndAdd(&lock->ticket);
  while (lock->turn != myturn){
    sleep(1); 
    // Spin. For some reason just having it do nothing
    // was super slow ^^^^
    //printf(1, "spinning...n");
  }
}

void lock_release(struct __lock_t *lock) {
  lock->turn = lock->turn + 1;
}

int FetchAndAdd(int *ptr) {
  int old = *ptr;
  *ptr = old + 1;
  return old;
}
