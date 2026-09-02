
#include "terrain.h"
#include <stdio.h>

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
  int x, y;
  char nom_fichier[100];

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  // Tentative d'ouverture du fichier avec le premier argument
  f = fopen(argv[1], "r");
  
  // Si le fichier ne s'ouvre pas correctement ou est vide, demander un autre nom de fichier
  while (f == NULL || fichier_est_vide(f)) {
    if (f == NULL) {
      printf("Erreur : fichier non trouvé. Taper un nouveau nom de fichier : ");
    } else {
      printf("Erreur : fichier vide. Taper un nouveau nom de fichier : ");
      fclose(f); // Fermer le fichier vide
    }
    scanf("%s", nom_fichier);
    f = fopen(nom_fichier, "r");
  }

  // Lecture du terrain
  erreur_terrain err = lire_terrain(f, &t, &x, &y);
  fclose(f);

  // Si une erreur survient pendant la lecture du terrain
  while (err != OK) {
    printf("Erreur lors de la lecture du fichier. Taper un nouveau nom de fichier : ");
    scanf("%s", nom_fichier);
    f = fopen(nom_fichier, "r");

    if (f != NULL && !fichier_est_vide(f)) {
      err = lire_terrain(f, &t, &x, &y);
      fclose(f);
    }
  }

  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);

  return 0;
}