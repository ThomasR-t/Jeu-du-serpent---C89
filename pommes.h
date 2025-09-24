#ifndef POMMES_H
#define POMMES_H
#include "serpent.h"
#include "graphique.h"
#include <graph.h>
#define LARGEUR 60
#define HAUTEUR 40
#define TAILLE_CASE 19
typedef struct PommeNode {
    Position position;
    struct PommeNode* next;
} PommeNode;
typedef struct Pommes {
    PommeNode* head;
    int nombre;
} Pommes;
void LibererPommes(Pommes* pommes);
void GenererPommes(Pommes* pommes);
void AjouterPomme(Pommes* pommes, int x, int y);
void GenererNouvellePomme(Pommes* pommes);
int CollisionAvecPommeSerpent(Position position, PommeNode* pommes);
int CollisionAvecPomme(Serpent* serpent, Pommes* pommes, int* score);
#endif
