#include <stdio.h>
#include <stdlib.h>
#include "observateur.h"
/*
typedef enum {
    A,
    G, 
    D, 
    M  
} alphabet;

typedef enum {
    Init,   // État initial
    lit_M,  // Après avoir lu M
    Er      // État d'erreur
} etat;

typedef struct {
    etat etatCourant;
} Automate;
*/

// Fonction pour initialiser l'automate
/*
void init_automate(Automate *automate) {
    automate->etatCourant = Init;
}
*/
void initialiser_automate(Automate *automate) {
    automate->etatCourant = Init;
}

etat etat_courant(Automate *automate) {
    return automate->etatCourant;
}

// Fonction de transition
void transition(Automate *automate, alphabet alpha) {
    switch (automate->etatCourant) {
        case Init:
            if (alpha == M) {
                automate->etatCourant = lit_M;
            } else if (alpha == A) {
                automate->etatCourant = Er;
            } else {
                automate->etatCourant = Init; // G et D ne changent rien
            }
            break;

        case lit_M:
            if (alpha == A) {
                automate->etatCourant = Init; // Retour à l'état initial après un déplacement valide
            } else if (alpha == M || alpha == G || alpha == D) {
                automate->etatCourant = lit_M; // Reste en lit_M
            }
            break;

        case Er:
            automate->etatCourant = Er; // Reste en erreur
            break;

        default:
            printf("État inconnu\n");
            break;
    }
}

// Fonction pour afficher l'état actuel (à des fins de test/debugging)
void afficher_etat(Automate *automate) {
    switch (automate->etatCourant) {
        case Init:
            printf("État actuel : Init\n");
            break;
        case lit_M:
            printf("État actuel : lit_M\n");
            break;
        case Er:
            printf("État actuel : Erreur\n");
            break;
    }
}
/*
// Exemple d'utilisation
int main() {
    Automate automate;
    initialiser_automate(&automate);

    alphabet sequence[] = {M, A, G, M, D, M, A, A}; // Séquence test
    int taille = sizeof(sequence) / sizeof(sequence[0]);

    for (int i = 0; i < taille; i++) {
        printf("Lecture de : %c\n", sequence[i] == M ? 'M' : sequence[i] == A ? 'A' : sequence[i] == G ? 'G' : 'D');
        transition(&automate, sequence[i]);
        afficher_etat(&automate);

        if (automate.etatCourant == Er) {
            printf("Erreur détectée dans la séquence.\n");
            break;
        }
    }

    return 0;
}
*/