#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include "ligne_commande.h"

int main()
{
    printf("Bienvenue sur mon shell\n");
    bool fini = false;
    while (!fini) {
        printf(">>> ");
        fflush(stdout);

        char** commande = lis_ligne();

        if (commande == NULL) {
            printf("Au revoir\n");
            fini = true;
        } else {
            if (commande[0] != NULL) {
                pid_t pid = fork();
                
                // Vérification que la commande est valide (pas vide)
                if (pid < 0) {
                    perror("Erreur lors de fork");
                } else if (pid == 0) {
                    // Fils
                    execvp(commande[0], commande);
                    perror("Erreur lors de execvp"); // Affichage d'erreur si execvp échoue
                    _exit(1); // Terminer le processus fils si exec échoue
                } else {
                    // Parent : attendre la terminaison du fils
                    wait(NULL);
                }
            }
        }
    }
    return 0;
}
