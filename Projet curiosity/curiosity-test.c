#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdlib.h>

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}
void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}



int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;

  if (argc < 2) {
    printf("Usage: %s <fichier test>\n", argv[0]);
    return 1;
  }

  char terrain[100];
  char programme[100];
  int nb_pas, pos_x, pos_y;
  char e, o, e1;

  FILE* fichier = NULL;
  fichier = fopen(argv[1], "r");

  if (fichier != NULL){

    //récupération des arguements dans le fichier en parametre
    fscanf(fichier,"%s",terrain);//nom du fichier terrain
    fscanf(fichier,"%s",programme);//nom du fichier programme
    fscanf(fichier,"%d",&nb_pas);//nombre de pas maximium
    fscanf(fichier,"%c",&e1);
    fscanf(fichier,"%c",&e);//évènement attendu
    e1 = e;
    if (e == 'N' || e == 'F'){
        //printf("e : %c\n",e);
        fscanf(fichier,"%d",&pos_x);//position x
        fscanf(fichier,"%d",&pos_y);//position y
        fscanf(fichier,"%s",&o);//orientation
        //printf("e : %c\n",e);
        //pour débuguer
        //printf("pos_x : %d\n",pos_x);
        //printf("pos_y : %d\n",pos_y);
    }
    //printf("e : %c\n",e);
    //printf("e1 : %c\n",e1);
    //printf("nb_pas : %d\n",nb_pas);
    

    //Lecture du terrain, initialisation de la position du robot
    errt = initialise_environnement(&envt,terrain);
    gestion_erreur_terrain(errt);

    //Lecture du programme 
    errp = lire_programme(&prog,programme);
    gestion_erreur_programme(errp);

    //Initialisation de l'état
    init_etat(&etat);
    int pas = 1;
    while(pas <= nb_pas && res == OK_ROBOT){
        res = exec_pas(&prog, &envt, &etat);
        afficher_envt(&envt);
        pas++;
    }
    //printf("res : %d\n",res);

    /* Affichage du résultat */
  switch (e1) {
    case 'N':
        if (res == OK_ROBOT){
            printf("Tout c'est passé comme prévue, le robot est sur une case libre \n");
        }else{
            printf("Le robot n'est pas sur une case libre ou le programme est terminé mais aurait du l'être !!!\n");
        }
        if (pos_x == abscisse(&envt.r) && pos_y == ordonnee(&envt.r)){
            printf("Les coordonnées sont OK\n");

        }else{
            printf("les coordonees sont mauvaises");
        }
        if ((orient(&envt.r)==Nord && o == 'N') || (orient(&envt.r)==Est && o == 'E')||(orient(&envt.r)==Sud && o == 'S')||(orient(&envt.r)==Ouest && o == 'O')){
            printf("L'orientation est OK\n");

        }else{
            printf("L'orientation est mauvaise");
        }
        break;

    case 'F':
        if (res == ARRET_ROBOT){
            printf("Tout c'est passé comme prévue, le programme est terminé \n");
        }else{
            printf("Le programme aurait du être terminé mais ce n'est pas le cas !!!\n");
        }
        if (pos_x == abscisse(&envt.r) && pos_y == ordonnee(&envt.r)){
            printf("Les coordonnées sont OK\n");

        }else{
            printf("les coordonees sont mauvaises");
        }
        if ((orient(&envt.r)==Nord && o == 'N') || (orient(&envt.r)==Est && o == 'E')||(orient(&envt.r)==Sud && o == 'S')||(orient(&envt.r)==Ouest && o == 'O')){
            printf("L'orientation est OK\n");

        }else{
            printf("L'orientation est mauvaise\n");
        }
        break;
    case 'S':
        if (res == SORTIE_ROBOT){
             printf("Le robot est sortie comme prévue\n");
        }else{
            printf("Le robot aurait du sortir mais ce n'est pas le cas !!!\n");           
        }
        break;
    case 'O':
        if (res == CRASH_ROBOT){
            printf("Le robot s'est écrasé comme prévue\n");
        }else{
            printf("Le robot aurait du s'écraser mais ce n'est pas le cas !!!\n");           
        }
        break;
    case 'P':
        if (res == PLOUF_ROBOT){
            printf("Le robot est tombé dans l'eau comme prévue\n");
        }else{
            printf("Le robot aurait du tomber dans l'eau mais ce n'est pas le cas !!!\n");           
        }
        break;
    default:
        printf("DEFAULT\n");
        break; 
    }
    
    fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
        return 1;
    }
    return 0;

}