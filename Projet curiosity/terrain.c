
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l, h;   // Dimensions du terrain
  char ligne[DIM_MAX];

  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  // Lecture des dimensions
  fscanf(f, "%d", &l);  // Largeur
  fscanf(f, "%d", &h);  // Hauteur
  t->largeur = l;
  t->hauteur = h;
  fscanf(f, "\n");  // Saut de ligne après les dimensions

  // Lecture du terrain
  for (int j = 0; j < h; j++) {
    fgets(ligne, DIM_MAX, f);
    for (int i = 0; i < l; i++) {
      switch (ligne[i]) {
        case '.':
          t->tab[i][j] = LIBRE;
          break;
        case '#':
          t->tab[i][j] = ROCHER;
          break;
        case '~':
          t->tab[i][j] = EAU;
          break;
        case 'C':
          t->tab[i][j] = LIBRE;  // La case où est le robot est libre
          *x = i;  // Coordonnée x du robot
          *y = j;  // Coordonnée y du robot
          break;
        default:
          return ERREUR_FICHIER;  // Si un caractère inattendu est trouvé
      }
    }
  }

  return OK;
}

/* À compléter */

/* Largeur d'un terrain */
int largeur(Terrain *t){
  return t->largeur;
}

/* Hauteur d'un terrain */
int hauteur(Terrain *t){
  return t->hauteur;
}


/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int est_case_libre(Terrain *t, int x, int y){
  int l = largeur(t);
  int h = hauteur(t);
  return ((0 <= x && x < l) && (0 <= y && y < h) && t->tab[y][x] == LIBRE);
}


/* Affichage d'un terrain t sur la sortie standard */
void afficher_terrain(Terrain *t){
  int l = largeur(t);
  int h = hauteur(t);
 // Parcours du terrain pour afficher chaque case
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < l; i++) {
      switch (t->tab[j][i]) { // On parcourt le terrain
        case LIBRE:
          printf(".");  // Affiche '.' pour une case libre
          break;
        case ROCHER:
          printf("#");  // Affiche '#' pour un rocher
          break;
        case EAU:
          printf("");  // Affiche '' pour de l'eau
          break;
        default:
          printf("C");  // En cas de case non reconnue, on affiche '?'
          break;
      }
    }
    printf("\n");  // Nouvelle ligne après chaque ligne du terrain
  }
}



/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y) {
  if (f == NULL) {
    printf("Erreur : fichier non ouvert.\n");
    return;
  }
  // Écrire les dimensions du terrain
  fprintf(f, "%d\n", t->largeur);
  fprintf(f, "%d\n", t->hauteur);

  // Écrire le terrain case par case
  for (int j = 0; j < t->hauteur; j++) {
    for (int i = 0; i < t->largeur; i++) {
      if (i == x && j == y) {
        // Si c'est la position du robot, écrire 'C'
        fprintf(f, "C");
      } else {
        // Sinon, écrire le type de case
        switch (t->tab[i][j]) {
          case LIBRE:
            fprintf(f, ".");
            break;
          case ROCHER:
            fprintf(f, "#");
            break;
          case EAU:
            fprintf(f, "~");
            break;
          default:
            fprintf(f, "?"); // En cas d'erreur inattendue
            break;
        }
      }
    }
    fprintf(f, "\n"); // Passer à la ligne suivante après chaque ligne du terrain
  }
}