// thread nonsense

int thread_create(void (*fcn)(void *, void *), void *arg1, void *arg2);
int thread_join();

// lock nonsense

typedef struct __lock_t {
  int ticket;
  int turn;
} lock_t;

void lock_init(struct __lock_t *lock);
void lock_acquire(struct __lock_t *lock);
void lock_release(struct __lock_t *lock);
int FetchAndAdd(int *ptr);
