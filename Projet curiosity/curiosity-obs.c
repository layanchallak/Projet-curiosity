#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_pile.h"
#include "environnement.h"
#include "programme.h"
#include "observateur.h"
#include "interprete.h"

// Fonction pour convertir une commande en alphabet
alphabet convertir_en_alphabet(char cmd) {
    switch (cmd) {
        case 'M': return M;  // Mesure
        case 'A': return A;  // Avance
        case 'G': return G;  // Gauche
        case 'D': return D;  // Droite
        default: return A;   // Par défaut (ici, "A" comme choix arbitraire)
    }
}

// Fonction principale pour vérifier la propriété
void curiosity_obs(char *fichier_terrain, char *fichier_programme) {
    // Initialisation de l'environnement
    Environnement envt;
    if (initialise_environnement(&envt, fichier_terrain) != OK) {
        fprintf(stderr, "Erreur : terrain invalide\n");
        return;
    }

    // Lecture du fichier programme
    FILE *file = fopen(fichier_programme, "r");
    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier programme\n");
        return;
    }

    // Initialisation de l'automate
    Automate automate;
    initialiser_automate(&automate);

    // Initialisation de la pile pour gérer les groupes différés
    PileEntiers pile;
    creer_pile(&pile);

    // Variable pour suivre si une mesure a été effectuée avant une avance
    int mesure_effectuee = 0;

    // Lecture des commandes
    char cmd[256];
    while (fscanf(file, "%s", cmd) != EOF) {
        for (size_t i = 0; i < strlen(cmd); i++) {
            char current = cmd[i];

            if (current == '{') {
                // Début d'un groupe différé
                for (i++; cmd[i] != '}' && cmd[i] != '\0'; i++) {
                    empiler(&pile, cmd[i]);
                }
            } else if (current == '!') {
                // Exécution différée
                while (!est_vide(&pile)) {
                    char deferred_cmd = depiler(&pile);
                    alphabet alpha = convertir_en_alphabet(deferred_cmd);
                    transition(&automate, alpha);

                    // Vérification de la propriété
                    if (deferred_cmd == 'A' && !mesure_effectuee) {
                        printf("Propriété violée : avance sans mesure (dans un groupe différé).\n");
                        fclose(file);
                        return;
                    }
                    if (deferred_cmd == 'M') {
                        mesure_effectuee = 1;
                    }
                }
            } else if (current == '?') {
                // Commande conditionnelle (lecture complète attendue)
                if (i + 2 < strlen(cmd)) {
                    int n = cmd[i - 1] - '0';
                    char exec_cmd = (n != 0) ? cmd[i + 1] : cmd[i + 2];
                    alphabet alpha = convertir_en_alphabet(exec_cmd);
                    transition(&automate, alpha);

                    // Vérification de la propriété
                    if (exec_cmd == 'A' && !mesure_effectuee) {
                        printf("Propriété violée : avance sans mesure (dans une condition).\n");
                        fclose(file);
                        return;
                    }
                    if (exec_cmd == 'M') {
                        mesure_effectuee = 1;
                    }
                    i += 2;  // Avance après le traitement
                }
            } else {
                // Commande simple
                alphabet alpha = convertir_en_alphabet(current);
                transition(&automate, alpha);

                // Vérification de la propriété
                if (current == 'A' && !mesure_effectuee) {
                    printf("Propriété violée : avance sans mesure.\n");
                    fclose(file);
                    return;
                }
                if (current == 'M') {
                    mesure_effectuee = 1;
                }
            }
        }
    }

    fclose(file);
    printf("La propriété est valide.\n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_terrain> <fichier_programme>\n", argv[0]);
        return EXIT_FAILURE;
    }

    curiosity_obs(argv[1], argv[2]);
    return EXIT_SUCCESS;
}