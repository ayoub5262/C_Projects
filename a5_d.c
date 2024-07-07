#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[] )  {
	
	if (argc != 8) {
        fprintf(stderr, "Usage: %s <breite> <hoehe> <radius> <rot> <gruen> <blau> <Dateiname>.ppm\n", argv[0]);
        return -1;
    }

    int breite, hoehe, radius, rot, gruen, blau;
    sscanf(argv[1], "%d", &breite);
    sscanf(argv[2], "%d", &hoehe);
    sscanf(argv[3], "%d", &radius);
    if(breite < 1 || hoehe < 1 || radius < 1){
        fprintf(stderr, "Breite, Hoehe und radius duerfen nicht weniger als 1 sein.\n");
        return -1;
    }

    sscanf(argv[4], "%d", &rot);
    if(rot < 0) rot = 0;
    if(rot > 255) rot = 255;

    sscanf(argv[5], "%d", &gruen);
    if(gruen < 0) gruen = 0;
    if(gruen > 255) gruen = 255;

    sscanf(argv[6], "%d", &blau);
    if(blau < 0) blau = 0;
    if(blau > 255) blau = 255;

    char *file_path = argv[7];
    
	// Datei oeffnen
    FILE *file = fopen(file_path, "w");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei");
        return -1;
    }

    fprintf(file, "P3 %d %d 255 ", breite, hoehe);

    int cx = breite / 2;
    int cy = hoehe / 2;

    for (int x = 0; x < breite; ++x) {
        for (int y = 0; y < hoehe; ++y) {
            int dx = x - cx;
            int dy = y - cy;
            int dist = dx * dx + dy * dy;
            if (abs(dist - radius * radius) <= radius)
                fprintf(file, "%d %d %d ", rot, gruen, blau);
            else  fprintf(file, "0 0 0 ");
        }
        fprintf(file, "\n");
    }
    fclose(file);

    return 0;
}