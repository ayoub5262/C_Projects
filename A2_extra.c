#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int tueten = 40;
int num_threads = 5;
sem_t sem;

void *verteilen(void *arg){
    while(tueten > 0){
        if(sem_wait(&sem)){
            perror("Fehler bei der Sperre\n");
            pthread_exit(NULL);
        }
        printf("Verbleibende Tueten: %d , Helfer %ld verteilte jetzt\n", tueten--, (long) arg + 1);
        if(sem_post(&sem)){
            perror("Fehler bei der Entsperrung\n");
            pthread_exit(NULL);
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t helfer[num_threads];
    int result_thread;
    if(sem_init(&sem, 0, 1)){
        perror("Fehler bei der Initialisierung des sem\n");
        exit(-1);
    }

    for(long i = 0; i < num_threads; i++){
        printf("Helfer %ld wurde erstellt\n", i + 1);
        if(pthread_create(&helfer[i], NULL, verteilen, (void *)i)){
            perror("Fehler bei der Erstellung des Threads\n");
            exit(-1);
        }
    }
    for(int i = 0; i < num_threads; i++)
        pthread_join(helfer[i], NULL);
    
    if(sem_destroy(&sem)){
        perror("Fehler bei der Zerstoerung des sem\n");
        exit(-1);
    }
    printf("Verbleibende Tueten %d\n", tueten);
    return 0;
}


