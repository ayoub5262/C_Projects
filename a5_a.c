#include <stdio.h>

int breite;
int hoehe;
long dateigroesse;

int main( int argc, char *argv[] )  {
	
	if (argc != 2) {
        fprintf(stderr, "Usage: %s <Dateiname>.ppm\n", argv[0]);
        return -1;
    }

	// Datei oeffnen
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei");
        return -1;
    }

    char format[2];

    // Dateikopf lesen
    if (fscanf(file, "%2c", format) != 1 || format[0] != 'P' || format[1] != '3') {
        fprintf(stderr, "Invalid PPM format\n");
        fclose(file);
        return -1;
    }

    int max_helligkeit;
	
    if (fscanf(file, "%d %d %d", &breite, &hoehe, &max_helligkeit) != 3) {
        fprintf(stderr, "Fehler beim lesen von Breite, hoehe oder Maximalwert der Helligkeit\n");
        fclose(file);
        return -1;
    }

    // Dateigroesse nehmen 
    fseek(file, 0, SEEK_END);
    dateigroesse = ftell(file);
    fclose(file);

    // Ergebnisse ausgeben
	printf("Breite: %d \nHoehe: %d \nDateigroesse: %ld bytes\n",breite,hoehe,dateigroesse);
	return 0;
}