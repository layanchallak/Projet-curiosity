#include "robot.h"
#include "terrain.h"
#include <stdio.h>

#define TAILLE_TERRAIN 10

/* Affiche une orientation sur la sortie standard */
void afficher_orientation(Orientation o) {
  switch (o) {
  case Nord:
    printf("Nord\n");
    break;
  case Est:
    printf("Est\n");
    break;
  case Sud:
    printf("Sud\n");
    break;
  case Ouest:
    printf("Ouest\n");
    break;
  }
}

void afficher_infos_robot(Robot *r) {
  int x, y;
  int x1, y1;

  // Récupérer la position du robot
  position(r, &x, &y);
  // Récupérer la case devant le robot
  position_devant(r, &x1, &y1);
  // Afficher la position
  printf("Position : (%d, %d) - Orientation : ", x, y);
  afficher_orientation(orient(r));
  printf("\n");
}

// Fonction pour vérifier si le fichier est vide
int fichier_est_vide(FILE *f) {
  int ch = fgetc(f);
  if (ch == EOF) {
    return 1; // Le fichier est vide
  }
  ungetc(ch, f); // Remettre le caractère dans le flux si ce n'est pas vide
  return 0;
}

int main(int argc, char **argv) {
  FILE *f = NULL;
  Terrain t;
  Robot r;
  char c;
  int x, y;

  if (argc < 2) {
    printf("Usage : %s <fichier terrain>\n", argv[0]);
    return 1;
  }

  // Ouverture du fichier terrain
  f = fopen(argv[1], "r");
  
  // Si le fichier ne s'ouvre pas correctement ou est vide
  if (f == NULL || fichier_est_vide(f)) {
    printf("Erreur : fichier non trouvé ou fichier vide.\n");
    return 1;
  }

  // Lecture du terrain
  erreur_terrain err = lire_terrain(f, &t, &x, &y);
  fclose(f);

  // Gestion des erreurs lors de la lecture du terrain
  if (err != OK) {
    printf("Erreur lors de la lecture du terrain.\n");
    return 1;
  }

  // Initialiser le robot à la position lue dans le terrain
  init_robot(&r, x, y, Est); // Orientation par défaut : Est

  afficher_infos_robot(&r);

  printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
  scanf(" %c", &c);
  while (c != 'f') {
    if (c == 'a') {
      // Faire avancer le robot
      avancer(&r);
    } else if (c == 'g') {
      // Tourner à gauche
      tourner_a_gauche(&r);
    } else if (c == 'd') {
      // Tourner à droite
      tourner_a_droite(&r);
    } else {
      // Commande non reconnue
      printf("Commande inconnue, entrez 'a', 'g', 'd' ou 'f' pour quitter.\n");
    }
    // Afficher les informations du robot après chaque action
    afficher_infos_robot(&r);
    // Lire une nouvelle action
    printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : ");
    scanf(" %c", &c);
  }
  printf("Fin du programme.\n");
  return 0;
}