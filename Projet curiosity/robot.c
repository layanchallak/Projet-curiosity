
#include "robot.h"
#include "terrain.h"

/* initialiser le robot r en position (x,y) et orientation o */
void init_robot(Robot *r, int x, int y, Orientation o){
    r->o = o ;
    r->x = x ;
    r->y = y ; 
}

/* faire avancer le robot d'une case */
void avancer(Robot *r){
    //verifier case est libre ?????          , prend en compte l'orientation de robot 
    Orientation or_Robot = r->o;
    switch (or_Robot)
    {
    case Est:
        r->x++;
        break;
    case Nord:
        r->y--;
    case Ouest:
        r->x--;
    case Sud :
        r->y++;
    }
}

/* faire tourner le robot à gauche */
void tourner_a_gauche(Robot *r){
    //prend compte l'orientation 
    Orientation or_Robot = r->o;
    switch (or_Robot)
    {
    case Est:
        r->o = Nord ; 
        break;
    case Ouest :
        r->o = Sud ;
        break;
    case Nord :
        r->o = Ouest ; 
        break;
    case Sud :
        r->o = Est;
        break;
    }
}

/* faire tourner le robot à droite */
void tourner_a_droite(Robot *r){
    //prend compte l'orientation 
    Orientation or_Robot = r->o;
    switch (or_Robot)
    {
    case Est:
        r->o = Sud ; 
        break;
    case Ouest :
        r->o = Nord ;
        break;
    case Nord :
        r->o = Est ; 
        break;
    case Sud :
        r->o = Ouest;
        break;
    }

}

/* recupere la position de la case du robot */
void position(Robot *r, int *x, int *y) {
    *x = r->x; 
    *y = r->y;  
}

/* recupere la position en abscisse de la case du robot */
int abscisse(Robot *r){
    return r->x;
}

/* recupere la position en ordonnee de la case du robot */
int ordonnee(Robot *r){
    return r->y;
}

/* recupere l'orientation du robot */
Orientation orient(Robot *r){
    return r->o;
}

/* recupere la position de la case devant le robot */
void position_devant(Robot *r, int *x, int *y){
    // Initialiser les coordonnées à la position actuelle du robot
    *x = r->x;
    *y = r->y;
    switch (r->o) {
        case Nord:
            (*y)--;  
            break;
        case Est:
            (*x)++;  
            break;
        case Sud:
            (*y)++;  
            break;
        case Ouest:
            (*x)--;  
            break;
    }
}