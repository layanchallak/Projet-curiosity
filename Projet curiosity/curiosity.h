#ifndef CURIOSITE_H
#define CURIOSITE_H

#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure EtatRobot
typedef struct {
    int x;
    int y;
    char direction;  // Vous pouvez choisir un type pour la direction (ex. : 'N' pour nord, 'S' pour sud, etc.)
} EtatRobot;

// Déclarations de fonctions
void gestion_erreur_terrain(erreur_terrain e);
void affichage_position_programme(erreur_programme e);
void gestion_erreur_programme(erreur_programme e);

int main(int argc, char **argv);
EtatRobot initialiser_robot(Terrain *terrain);

#endif // CURIOSITE_H
