#include "generation_terrains.h"
#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "robot.h"
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
  int N, l, h;
  float dObst;
  float graine;
  int nb_step_max;
  FILE *fichier_res;


  if (argc < 9) {
    printf(
        "Usage: %s <fichier_programme> <N> <largeur> <hauteur> <densite_obstacle> <graine> <nb_step_max> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[2], NULL, 10);
  l = strtol(argv[3], NULL, 10);
  h = strtol(argv[4], NULL, 10);
  dObst = strtof(argv[5], NULL);
  graine = strtof(argv[6], NULL);
  nb_step_max = strtol(argv[7], NULL, 10);

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
  fichier_res = fopen(argv[8], "w");
  // Écriture du nombre de terrains
  fprintf(fichier_res, "%d\n", N);

  // Initialisation de la fonction random
  srand(graine);
  int nb_terrains_valides = 0;
  Environnement envt;
  etat_inter etat;
  resultat_inter res;
  Programme prog;
  int nb_step;
  int nb_sortie = 0;
  int nb_plouf = 0;
  int nb_crash = 0;
  int nb_bloquage = 0;
  int somme_pas = 0;
  int nb_step_max_init = nb_step_max;


  while (nb_terrains_valides < N){
    generation_aleatoire(&envt.t, l, h, dObst);
    if (existe_chemin_vers_sortie(&envt.t)) {
      nb_terrains_valides++;
      init_robot(&envt.r, l/2, h/2, Est);
      lire_programme(&prog, argv[1]);
      init_etat(&etat);
      nb_step = 0;
      do {
        res = exec_pas(&prog, &envt, &etat);
        nb_step++;
        nb_step_max_init--;
      } while (res == OK_ROBOT && nb_step_max_init > 0);
      nb_step_max_init = nb_step_max;
      switch (res) {
        case SORTIE_ROBOT:
          fprintf(fichier_res, "%d\n", nb_step);
          nb_sortie++;
          somme_pas += nb_step;
          break;
        case OK_ROBOT:
          fprintf(fichier_res, "-1\n");
          nb_bloquage++;
          break;
        case PLOUF_ROBOT:
          fprintf(fichier_res, "-2\n");
          nb_plouf++;
          break;
        case CRASH_ROBOT:
          fprintf(fichier_res, "-3\n");
          nb_crash++;
          break;
        default:
          break;
      }
    }
  }
  
  printf("Nombre de robots sortis : %d\n", nb_sortie);
  printf("Pourcentage de robots sortis : %d%%\n", (int)((float)nb_sortie / N * 100));
  printf("Nombre de robots ploufs : %d\n", nb_plouf);
  printf("Pourcentage de robots ploufs : %d%%\n", (int)((float)nb_plouf / N * 100));
  printf("Nombre de robots crashs : %d\n", nb_crash);
  printf("Pourcentage de robots crashs : %d%%\n", (int)((float)nb_crash / N * 100));
  printf("Nombre de robots bloqués : %d\n", nb_bloquage);
  printf("Pourcentage de robots bloqués : %d%%\n", (int)((float)nb_bloquage / N * 100));
  printf("Moyenne du nombre de pas : %f\n", (float)somme_pas / nb_sortie);

  // fermeture des fichiers
  fclose(fichier_res);
  return 0;
}