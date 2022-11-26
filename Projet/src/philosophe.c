#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

pthread_t* phil;
pthread_mutex_t* baguette;
int* nb_phil;

void* philosophe ( void* arg )
{
  int *id=(int *) arg;
  int left = *id;
  int right;
  if (*nb_phil == 1) {
    right = 1;
  } else {
    right = (left + 1) % *nb_phil;
  }
  int i = 0;
  while(i < 100000) {
    // philosophe pense
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
    i++;
  }
  return (NULL);
}

int main(int argc, char *argv[])
{
    nb_phil = (int *) malloc(sizeof(int));
    *nb_phil =  atoi(argv[1]);

    phil = (pthread_t *) malloc(*nb_phil * sizeof(pthread_t));

    if (*nb_phil == 1) {
        baguette = (pthread_mutex_t *) malloc((*nb_phil+1) * sizeof(pthread_mutex_t));

        for (int i = 0; i < (*nb_phil+1); i++) {
        pthread_mutex_init(&baguette[i], NULL);
        }
    } else {
        baguette = (pthread_mutex_t *) malloc(*nb_phil * sizeof(pthread_mutex_t));

        for (int i = 0; i < *nb_phil; i++) {
        pthread_mutex_init(&baguette[i], NULL);
        }
    }

    for (int i = 0; i < *nb_phil; i++) {
        int id = i;
        pthread_create(&phil[i], NULL, philosophe, &id);
    }
    for (int i = 0; i < *nb_phil; i++) {
        pthread_join(phil[i], NULL);
    }
    free(phil);
    free(baguette);

    return 0;
}
