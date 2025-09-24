#ifndef SERPENT_H
#define SERPENT_H
#include <graph.h>
#include <stdlib.h>
#define TAILLE_CASE 19
#define LARGEUR 60
#define HAUTEUR 40
typedef struct {
    int x;
    int y;
} Position;
typedef struct {
    Position* corps;
    int longueur;
} Serpent;
typedef struct Pommes Pommes;
typedef struct Obstacles Obstacles;
extern void DeplacerSerpent(Serpent* serpent, int* direction);
extern int GestionCollision(Serpent* serpent, Pommes* pommes, Obstacles* obstacles, int perdu, int* score);
extern int CollisionAvecSerpent(Serpent* serpent);
extern int EstDirectionOpposee(int directionActuelle, int nouvelleDirection);
extern int CollisionAvecBordures(Serpent* serpent);
int CollisionAvecPomme(Serpent* serpent, Pommes* pommes, int* score);
#endif // SERPENT_H
