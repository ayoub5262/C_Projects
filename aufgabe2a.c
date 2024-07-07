#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TUTEN 40 // Wir definieren NUM_TUTEN, weil wir es in global benutzen werden
int NUM_THREADS = 5;
int verbleibenden_tuten = NUM_TUTEN;

// Funktion, die die Arbeit eines Helfers simuliert
void *verteilen(void *arg) {
    long tid = (long)arg; // Thread-ID aus dem Argument extrahieren
    while (1) {
        if (verbleibenden_tuten > 0) {
            // Ausgabe und Anzahl der verbleibenden Tüten dekrementieren
            printf("Verbleibende Tüten: %d, Helfer #%ld verteilt eine Tüte. \n", verbleibenden_tuten, tid+1);
            verbleibenden_tuten--;
            sleep(1); // Simuliert das Austeilen einer Tüte durch eine Pause von 1 Sekunde
        } else {
            break; // Keine Tüten mehr übrig, Schleife beenden
        }
    }
    pthread_exit(NULL); // Thread beenden
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array zur Speicherung der Thread-IDs
    int rc; // Rückgabewert für die Fehlerüberprüfung
    long t; // Zählvariable

    // Erstellen der Helfer-Threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Erstellen Thread #%ld\n", t+1);
        rc = pthread_create(&threads[t], NULL, verteilen, (void *)t);
        if (rc) {
            perror("Fehler beim Erstellen des Threads");
            exit(-1); // Fehlerfall: Programm mit einem Fehlercode beenden
        }
    }
    // Warten auf das Ende aller Helfer-Threads
    for (t = 0; t < NUM_THREADS; t++) 
        pthread_join(threads[t], NULL);

    printf("Verbleibende Tüten: %d\n", verbleibenden_tuten);
    
    return 0;
}
