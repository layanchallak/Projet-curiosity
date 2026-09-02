#ifndef OBSERVATEUR_H   // Check if the macro is already defined
#define OBSERVATEUR_H   // Define the macro to indicate the file is included


#include <stdio.h>
#include <stdlib.h>

typedef enum {
    A,
    G, 
    D, 
    M  
}alphabet;

typedef enum {
    Init,   // État initial
    lit_M,  // Après avoir lu M
    Er,      // État d'erreur
}etat;

typedef struct {
    etat etatCourant;
}Automate;

// Fonction pour initialiser l'automate
//void init_automate(Automate *automate);
void initialiser_automate(Automate *automate);
etat etat_courant(Automate *automate);

// Fonction de transition
void transition(Automate *automate, alphabet alpha);


// Fonction pour afficher l'état actuel (à des fins de test/debugging)
void afficher_etat(Automate *automate) ;


// Exemple d'utilisation
//int main() ;

#endif // OBSERVATEUR_H