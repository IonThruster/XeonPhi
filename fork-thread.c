#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char msg[100] = "uninitialized";

void *Child_Thread(void *tid) {
  printf("In child  thread at %p: '%s':\n", &msg, msg);
  sleep(2);
  printf("In child  thread at %p: '%s':\n", &msg, msg);
  return 0;
}

void Parent_Thread() {
  sleep(1);
  strcpy(msg, "I'm a little teapot, short and stout");
  printf("In parent thread at %p: '%s':\n", &msg, msg);
}

int main() {
  pthread_t thr;

  pthread_create(&thr, NULL, Child_Thread, NULL); // Spawn thread

  Parent_Thread();

  pthread_exit(NULL);
  return 0;
}

/*
 * Compile Instructions : gcc -o fork-thread fork-thread.c -lpthread
 *
 */
