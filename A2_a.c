#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int tueten = 40;
int num_threads = 5;
pthread_mutex_t mutex;

void *verteilen(void *arg){
    while(tueten > 0){
        int result_mutex = pthread_mutex_lock(&mutex);
        if(result_mutex){
            perror("Fehler bei der Sperre\n");
            pthread_exit(NULL);
        }
        printf("Verbleibende Tueten: %d , Helfer %ld verteilte jetzt\n", tueten--, (long) arg + 1);
        result_mutex = pthread_mutex_unlock(&mutex);
        if(result_mutex){
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
    int result_mutex = pthread_mutex_init(&mutex, NULL);
    if(result_mutex){
        perror("Fehler bei der Initialisierung des Mutex\n");
        exit(-1);
    }

    for(long i = 0; i < num_threads; i++){
        printf("Helfer %ld wurde erstellt\n", i + 1);
        result_thread = pthread_create(&helfer[i], NULL, verteilen, (void *)i);
        if(result_thread){
            perror("Fehler bei der Erstellung des Threads\n");
            exit(-1);
        }
    }
    for(int i = 0; i < num_threads; i++)
        pthread_join(helfer[i], NULL);
    
    result_mutex = pthread_mutex_destroy(&mutex);
    if(result_mutex){
        perror("Fehler bei der Zerstoerung des Mutex\n");
        exit(-1);
    }
    printf("Verbleibende Tueten %d\n", tueten);
    return 0;
}


