#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N, i, l, h;
  float dObst;
  FILE *resFile;
  Terrain T;

  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  srand(time(NULL));

  int total_cases = l * h * N;
  int total_occupees = 0;
  int valid_terrains = 0;
  float densite_moyenne = 0.0;

  for (i = 0; i < N; i++) {
    // Générer un terrain valide (la validation est incluse dans generation_aleatoire)
    generation_aleatoire(&T, l, h, dObst);

    total_occupees += nb_cases_occupees(&T);

    // Calcul de la densité d'obstacle obtenue
    int occupees = nb_cases_occupees(&T);
    float densite_obstacle = (float)occupees / (l * h);

    // Vérifier si le terrain est valide
    if (existe_chemin_vers_sortie(&T)) {
      valid_terrains++;
    }

    // Écriture des terrains générés dans le fichier resFile
    ecrire_terrain(resFile, &T, l / 2, h / 2);
    fprintf(resFile, "Densité d'obstacle obtenue: %.2f\n", densite_obstacle);
  }

  // Calcul de la densité d'obstacle moyenne
  densite_moyenne = (float)total_occupees / (total_cases * N);
  // Calcul du pourcentage de terrains valides
  float pourcentage_valides = ((float)valid_terrains / N) * 100;

  // Écriture des statistiques finales dans le fichier
  fprintf(resFile, "Densité d'obstacle moyenne : %.2f\n", densite_moyenne);
  fprintf(resFile, "Pourcentage de terrains valides : %.2f%%\n", pourcentage_valides);

  // Affichage des statistiques dans le terminal
  printf("- Nombre total de terrains : %d\n", N);
  printf("- Dimensions de chaque terrain : %dx%d\n", l, h);
  printf("- Densité demandée : %.2f\n", dObst);
  printf("- Nombre total de cases occupées : %d\n", total_occupees);
  printf("- Proportion de cases occupées : %.2f%%\n", (total_occupees / (float)total_cases) * 100);

  // fermeture des fichiers
  fclose(resFile);
  return 0;
}