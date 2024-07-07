#include <stdio.h>


int main( int argc, char *argv[] )  {
	
	if (argc != 7) {
        fprintf(stderr, "Usage: %s <breite> <hoehe> <rot> <gruen> <blau> <Dateiname>.ppm\n", argv[0]);
        return -1;
    }

    int breite, hoehe, rot, gruen, blau;
    sscanf(argv[1], "%d", &breite);
    sscanf(argv[2], "%d", &hoehe);
    if(breite < 1 || hoehe < 1){
        fprintf(stderr, "Breite und Hoehe duerfen nicht weniger als 1 sein.\n");
        return -1;
    }

    sscanf(argv[3], "%d", &rot);
    if(rot < 0) rot = 0;
    if(rot > 255) rot = 255;

    sscanf(argv[4], "%d", &gruen);
    if(gruen < 0) gruen = 0;
    if(gruen > 255) gruen = 255;

    sscanf(argv[5], "%d", &blau);
    if(blau < 0) blau = 0;
    if(blau > 255) blau = 255;

    char *file_path = argv[6];
    
	// Datei oeffnen
    FILE *file = fopen(file_path, "w");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei");
        return -1;
    }

    fprintf(file, "P3 %d %d 255 ", breite, hoehe);
    for(int i = 0; i < breite*hoehe; i++)
        fprintf(file, "%d %d %d %s", rot, gruen, blau, (i%breite < breite-1 ? "" : "\n"));

    fclose(file);

    return 0;
}