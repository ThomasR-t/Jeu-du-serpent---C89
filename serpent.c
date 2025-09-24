#include "serpent.h"
#include "pommes.h"
void DeplacerSerpent(Serpent* serpent, int* direction) {
    couleur couleurFond = CouleurParComposante(0, 0, 0);
    couleur couleurSerpent = CouleurParComposante(255, 255, 0);
    couleur couleurTerrain = CouleurParComposante(111, 255, 94);
    couleur couleurTete = CouleurParComposante(168,65,38);
    // Clear the previous positions of the snake
    for (int i = 0; i < serpent->longueur; i++) {
        ChoisirCouleurDessin(couleurTerrain);
        RemplirRectangle(serpent->corps[i].x, serpent->corps[i].y, TAILLE_CASE, TAILLE_CASE);
    }
    // Update the snake's body positions
    for (int i = serpent->longueur - 1; i > 0; i--) {
        serpent->corps[i] = serpent->corps[i - 1];
    }
    // Move the snake's head based on the direction
    if (*direction == 1) {
        serpent->corps[0].x += TAILLE_CASE;
    } else if (*direction == 2) {
        serpent->corps[0].x -= TAILLE_CASE;
    } else if (*direction == 3) {
        serpent->corps[0].y -= TAILLE_CASE;
    } else if (*direction == 4) {
        serpent->corps[0].y += TAILLE_CASE;
    }
    // Draw the updated snake
    ChoisirCouleurDessin(couleurTete);
    RemplirRectangle(serpent->corps[0].x,serpent->corps[0].y,TAILLE_CASE, TAILLE_CASE);
    for (int i = 1; i < serpent->longueur; i++) {
        ChoisirCouleurDessin(couleurSerpent);
        RemplirRectangle(serpent->corps[i].x, serpent->corps[i].y, TAILLE_CASE, TAILLE_CASE);
    }
    Attendre(100);
}
int GestionCollision(Serpent* serpent, Pommes* pommes, Obstacles* obstacles, int perdu, int* score) {
    int loose = perdu;
    if (CollisionAvecPomme(serpent, pommes, score)) {
        serpent->longueur = serpent->longueur + 2;
        serpent->corps = realloc(serpent->corps, sizeof(Position) * serpent->longueur);
        loose = 1;
    }
    if (CollisionAvecObstacle(serpent, obstacles) || CollisionAvecSerpent(serpent) || CollisionAvecBordures(serpent)) {
        AfficherEcranFin(*score);
        Attendre(1000);
        loose = -1;
    }
    return loose;
}
int CollisionAvecSerpent(Serpent* serpent) {
    for (int i = 1; i < serpent->longueur; i++) {
        if (serpent->corps[0].x == serpent->corps[i].x && serpent->corps[0].y == serpent->corps[i].y) {
            return 1;
        }
    }
    return 0;
}
int EstDirectionOpposee(int directionActuelle, int nouvelleDirection) {
    if ((directionActuelle == 1 && nouvelleDirection == 2) ||
        (directionActuelle == 2 && nouvelleDirection == 1) ||
        (directionActuelle == 3 && nouvelleDirection == 4) ||
        (directionActuelle == 4 && nouvelleDirection == 3)) {
        return 1; // Les directions sont opposées
    }
    return 0; // Les directions ne sont pas opposées
}
int CollisionAvecBordures(Serpent* serpent) {
    if (serpent->corps[0].x < 0 || serpent->corps[0].x >= LARGEUR * TAILLE_CASE ||
        serpent->corps[0].y < 0 || serpent->corps[0].y >= HAUTEUR * TAILLE_CASE) {
        return 1;
    }
    return 0;
}
int CollisionAvecPomme(Serpent* serpent, Pommes* pommes, int* score) {
    PommeNode* current = pommes->head;
    PommeNode* prev = NULL;
    while (current != NULL) {
        if (serpent->corps[0].x >= current->position.x * TAILLE_CASE &&
            serpent->corps[0].x < (current->position.x + 1) * TAILLE_CASE &&
            serpent->corps[0].y >= current->position.y * TAILLE_CASE &&
            serpent->corps[0].y < (current->position.y + 1) * TAILLE_CASE) {
            // La pomme a été mangée, mettre à jour les liens
            if (prev == NULL) {
                // La pomme était en tête de liste
                pommes->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            *score = *score + 5;
            AfficherScore(*score);
            // Générer une nouvelle pomme
            GenererNouvellePomme(pommes);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}
