#include "obstacles.h"
void GenererObstacles(Obstacles* obstacles, Pommes* pommes, Serpent* serpent) {
    couleur couleurObstacle = CouleurParComposante(128, 128, 128);
    obstacles->positions = (Position*)malloc(obstacles->nombre * sizeof(Position));
    if (obstacles->positions == NULL) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < obstacles->nombre; i++) {
        do {
            obstacles->positions[i].x = rand() % LARGEUR;
            obstacles->positions[i].y = rand() % HAUTEUR;
        } while (CollisionAvecPommeSerpent(obstacles->positions[i], pommes->head) || CollisionAvecSerpent(serpent));
        ChoisirCouleurDessin(couleurObstacle);
        RemplirRectangle(obstacles->positions[i].x * TAILLE_CASE, obstacles->positions[i].y * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
    }
}
int CollisionAvecObstacle(Serpent* serpent, Obstacles* obstacles) {
    for (int i = 0; i < obstacles->nombre; i++) {
        if (serpent->corps[0].x == obstacles->positions[i].x * TAILLE_CASE &&
            serpent->corps[0].y == obstacles->positions[i].y * TAILLE_CASE) {
            return 1;
        }
    }
    return 0;
}
