#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include "../headers/stack.h"

sem_t* buffer_cons;
sem_t* buffer_prod;
stack_t stack;

pthread_mutex_t* counter_mutex_prod;
int counter_prod = 0;

pthread_mutex_t* counter_mutex_cons;
int counter_cons = 0;


void* productor(void* args) {
    if (counter_prod > 8192) {
        return NULL;
    }
    sem_wait(buffer_prod);
    for (int i = 0; i < 10000; i++) {
        // pass
    }
    pthread_mutex_lock(counter_mutex_prod);
    counter_prod++;
    pthread_mutex_unlock(counter_mutex_prod);
    sem_post(buffer_prod);
}

int main(int argc, char* argv) {
    int nb_thread_cons = atoi(argv[1]);
    int nb_thread_prod = atoi(argv[2]);

    sem_init(buffer_cons, 0 ,8);
    sem_init(buffer_prod, 0, 8)



}