#ifndef OBSTACLES_H
#define OBSTACLES_H
#include "pommes.h"
#include "serpent.h"
#define LARGEUR 60
#define HAUTEUR 40
#define TAILLE_CASE 19
typedef struct Obstacles {
    Position* positions;
    int nombre;
} Obstacles;
void GenererObstacles(Obstacles* obstacles, Pommes* pommes, Serpent* serpent);
int CollisionAvecObstacle(Serpent* serpent, Obstacles* obstacles);
#endif
