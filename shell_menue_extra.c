#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>    
#include <sys/wait.h>   

int main() {
    while (1) {  // Endlosschleife, um das Menü kontinuierlich anzuzeigen
        printf("Menü:\n1. ls -a\n2. cat Datei\n3. exit\n");  // Menü anzeigen
        printf("Bitte wählen Sie eine Option: ");
        int choice;
        scanf("%d", &choice);  // Benutzerauswahl einlesen
        while (getchar() != '\n');  // Eingabepuffer leeren

        if (choice == 3) {  // Wenn der Benutzer "exit" wählt
            printf("Programm beendet.\n");
            exit(0);  // Programm beenden
        }
        pid_t pid = fork();  // Neuen Prozess erstellen

        if (pid < 0) {  // Fehlerbehandlung für fork()
            perror("Fehler bei fork");
            exit(1);
        }
        if (pid == 0) {  // Im Kindprozess
            // Je nach Benutzerauswahl das entsprechende Programm ausführen
            if (choice == 1) 
                execlp("ls", "ls", "-a", NULL);  // "ls -a" ausführen
                
             else if (choice == 2) {
                char dateiname[256];
                printf("Bitte geben Sie den Dateinamen ein: ");
                scanf("%255s", dateiname);  // Dateinamen einlesen
                execlp("cat", "cat", dateiname, NULL);  // "cat dateiname" ausführen
            }
            
            perror("Fehler bei execlp");  // Fehlerbehandlung für execlp()
            exit(1);
        } else {  // Im Elternprozess
            int status;
            waitpid(pid, &status, 0);  // Auf Beendigung des Kindprozesses warten
            // PID und Exit-Status des Kindprozesses ausgeben
            printf("\nKindprozess mit PID %d beendet mit Status %d\n", pid, WEXITSTATUS(status));
        }
    }
    return 0;
}
