#include <stdio.h>
#include <pthread.h>

OSSpinLock count_spin;

static volatile int counter = 0;

void *mythread(void *arg) {

  pthread_spin_lock(&count_spin);

  printf("%s:begin \n", (char *) arg);
  int i;
  for (i = 0; i < 1e7; i++) {
    counter++;
  }
  printf("%s: done\n", (char *) arg);

  pthread_spin_unlock(&count_spin);
}

int main(int argc, char *argv[]) {

  pthread_t p1, p2, p3, p4, p5;

  printf("main: begin (counter = %d)\n", counter);
  pthread_spin_init(&count_spin, 0);

  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");
  pthread_create(&p3, NULL, mythread, "C");
  pthread_create(&p4, NULL, mythread, "D");
  pthread_create(&p5, NULL, mythread, "E");

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);

  printf("main: end (counter = %d)\n", counter);
  return 0;
}
