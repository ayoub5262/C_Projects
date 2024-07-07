#include <stdio.h>

// Funktion, die überprüft, ob eine gegebene Zahl eine Primzahl ist oder nicht
int ist_prim(int num) {
    if (num <= 1) return 0;                // Wenn die Zahl kleiner oder gleich 1 ist, ist sie keine Primzahl
    for (int i = 2; i * i <= num; i++) {   // Überprüfe alle Zahlen bis zur Quadratwurzel der gegebenen Zahl
        if (num % i == 0) return 0;// Wenn die Zahl durch irgendeine Zahl ohne Rest teilbar ist, ist sie keine Primzahl
    }
    return 1;                      // Wenn keine der Bedingungen zutrifft, ist die Zahl eine Primzahl
}

int main(){
    for ( int i = 2 ; i <= 20; i++){ // Durchlaufe alle Zahlen von 2 bis zur Obergrenze
        if (is_prime(i))             // Überprüfe, ob die aktuelle Zahl eine Primzahl ist
            printf("%i, ", i);       // Wenn ja, drucke die Zahl aus
    }
    printf("\n");           // Drucke eine neue Zeile am Ende des Programms
    return 0;               // Beende das Programm erfolgreich
}
