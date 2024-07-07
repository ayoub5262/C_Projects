#include <stdio.h>
#include <stdlib.h>

// Funktion, die überprüft, ob eine gegebene Zahl eine Primzahl ist oder nicht
int ist_prim(int num) {
    if (num <= 1) return 0;                // Wenn die Zahl kleiner oder gleich 1 ist, ist sie keine Primzahl
    for (int i = 2; i * i <= num; i++) {   // Überprüfe alle Zahlen bis zur Quadratwurzel der gegebenen Zahl
        if (num % i == 0) return 0;// Wenn die Zahl durch irgendeine Zahl ohne Rest teilbar ist, ist sie keine Primzahl
    }
    return 1;                      // Wenn keine der Bedingungen zutrifft, ist die Zahl eine Primzahl
}

int main(int argc, char *argv[]) {
    if (argc != 2) {   // Überprüfe, ob ein Argument übergeben wurde
        // Fehlermeldung, wenn kein Argument übergeben wurde
        printf("Fehler: Keine Obergrenze für Primzahlen übergeben\n");
        return 1; // Beende das Programm mit einem Fehlercode
    }

    int oberGrenze = atoi(argv[1]);  // Konvertiere das übergebene Argument in eine Ganzzahl
    // Durchlaufe alle Zahlen von 2 bis zur Obergrenze
    for (int i = 2; i <= oberGrenze; i++) {
        if (ist_prim(i))         // Überprüfe, ob die aktuelle Zahl eine Primzahl ist
            printf("%d,", i);       // Wenn ja, drucke die Zahl aus
    }
    printf("\n");                   // Drucke eine neue Zeile am Ende des Programms
    return 0;                       // Beende das Programm erfolgreich
}
