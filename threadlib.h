// thread nonsense

int thread_create(void (*fcn)(void *, void *), void *arg1, void *arg2);
int thread_join();

// lock nonsense

typedef struct __lock_t {
  int ticket;
  int turn;
} lock_t;

void lock_init(lock_t *lock);
void lock_acquire(lock_t *lock);
void lock_release(lock_t *lock);
int FetchAndAdd(int *ptr);
