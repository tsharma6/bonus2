#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t count_sem;

static volatile int counter = 0;

void *mythread(void *arg) {

  sem_wait(&count_sem);

  printf("%s:begin \n", (char *) arg);
  int i;
  for (i = 0; i < 1e7; i++) {
    counter++;
  }
  printf("%s: done\n", (char *) arg);

  sem_post(&count_sem);
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("In semaphore\n");

  pthread_t p1, p2, p3, p4, p5;

  printf("main: begin (counter = %d)\n", counter);
  sem_init(&count_sem, 0, 1);

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
