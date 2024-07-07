#include <stdio.h>


int main( int argc, char *argv[] )  {
	
	if (argc != 10) {
        fprintf(stderr, "Usage: %s <Breite> <Höhe> <Rotanteil Startfarbe> <Grünanteil Startfarbe> ",argv[0]);
        fprintf(stderr, "<Blauanteil Startfarbe>  <Rotanteil Zielfarbe> <Grünanteil Zielfarbe> <Blauanteil Zielfarbe> <Dateiname>.ppm\n");
        return -1;
    }

    int breite, hoehe, start_rot, ziel_rot, start_gruen, ziel_gruen, start_blau, ziel_blau;
    sscanf(argv[1], "%d", &breite);
    sscanf(argv[2], "%d", &hoehe);
    if(breite < 1 || hoehe < 1){
        fprintf(stderr, "Breite und Hoehe duerfen nicht weniger als 1 sein.\n");
        return -1;
    }

    sscanf(argv[3], "%d", &start_rot);
    if(start_rot < 0) start_rot = 0;
    if(start_rot > 255) start_rot = 255;
    sscanf(argv[6], "%d", &ziel_rot);
    if(ziel_rot < 0) ziel_rot = 0;
    if(ziel_rot > 255) ziel_rot = 255;

    sscanf(argv[4], "%d", &start_gruen);
    if(start_gruen < 0) start_gruen = 0;
    if(start_gruen > 255) start_gruen = 255;
    sscanf(argv[7], "%d", &ziel_gruen);
    if(ziel_gruen < 0) ziel_gruen = 0;
    if(ziel_gruen > 255) ziel_gruen = 255;

    sscanf(argv[5], "%d", &start_blau);
    if(start_blau < 0) start_blau = 0;
    if(start_blau > 255) start_blau = 255;
    sscanf(argv[8], "%d", &ziel_blau);
    if(ziel_blau < 0) ziel_blau = 0;
    if(ziel_blau > 255) ziel_blau = 255;

    char *file_path = argv[9];
    
	// Datei oeffnen
    FILE *file = fopen(file_path, "w");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei");
        return -1;
    }

    fprintf(file, "P3 %d %d 255 ", breite, hoehe);
    for (int y = 0; y < hoehe; ++y) {
        for (int x = 0; x < breite; ++x) {
            float ratio = (float)x / (breite - 1);
            int rot = start_rot + ratio * (ziel_rot - start_rot);
            int gruen = start_gruen + ratio * (ziel_gruen - start_gruen);
            int blau = start_blau + ratio * (ziel_blau - start_blau);
            fprintf(file, "%d %d %d ", rot, gruen, blau);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return 0;
}