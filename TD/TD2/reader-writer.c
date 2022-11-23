#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>

#define NTHREADS 4

/*
On favorise les writer ici
*/

pthread_mutex_t m_rcount;
pthread_mutex_t m_wcount;

sem_t wsem; // accès à la wsem
sem_t rsem; // bloque les lecteurs

int readcount=0; // nombre de readers
int writecount=0; // nombre de writers

int global_count=0;

void* writer(void* param) {
    int x = 0;
    while(x == 0) {
        pthread_mutex_lock(&m_wcount);
        writecount++;
        if(writecount == 1) {
            // Si première écrivain --> On bloque les prochains reader d'arriver
            sem_wait(&rsem); 
        }
        pthread_mutex_unlock(&m_wcount);        

        sem_wait(&wsem); // On attend maintenant que tous les reader on finis

        global_count++;
        printf("Writer: %d\n", global_count);

        sem_post(&wsem);

        pthread_mutex_lock(&m_wcount);
        writecount--;
        if(writecount == 0) {
            sem_post(&rsem);
        } 
        pthread_mutex_unlock(&m_wcount);
        x++;
    }
    return NULL;
}


void* reader(void* param) {
    int x = 0;
    while(x == 0) {
        sem_wait(&rsem); // Permet de bloquer les reader avec le writer
        pthread_mutex_lock(&m_rcount);
        // section critique
        readcount++;
        if (readcount==1) { // arrivée du premier reader
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&m_rcount);
        sem_post(&rsem); // Libère la sem quand il a finis 

        printf("Gloabl count : %d \n", global_count);

        pthread_mutex_lock(&m_rcount);
        // section critique
        readcount--;
        if(readcount==0) { // départ du dernier reader
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&m_rcount);
        x++;
    }
    return NULL;
}

int main() 
{
    sem_init(&wsem, 0, 1);
    sem_init(&rsem, 0, 1);

    pthread_t threads_reader[NTHREADS];
    pthread_t threads_writer[NTHREADS];
    for (int i=0; i<NTHREADS; i++) {
        pthread_create(&threads_reader[i], NULL, &reader, NULL);
        pthread_create(&threads_writer[i], NULL, &writer, NULL);
    }
    for (int i=0; i<NTHREADS; i++) {
        pthread_join(threads_reader[i], NULL);
    }
    return 0;
}