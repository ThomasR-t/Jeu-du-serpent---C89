#include <stdlib.h>
#include <graph.h>
#include "pommes.h"
void LibererPommes(Pommes* pommes) {
    PommeNode* current = pommes->head;
    while (current != NULL) {
        PommeNode* next = current->next;
        free(current);
        current = next;
    }
    pommes->head = NULL;
}
void GenererPommes(Pommes* pommes) {
    couleur couleurPommes = CouleurParComposante(255, 0, 0);
    pommes->head = NULL;
    for (int i = 0; i < pommes->nombre; i++) {
        PommeNode* nouvellePomme = (PommeNode*)malloc(sizeof(PommeNode));
        if (nouvellePomme == NULL) {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }
        nouvellePomme->position.x = rand() % LARGEUR;
        nouvellePomme->position.y = rand() % HAUTEUR;
        nouvellePomme->next = pommes->head;
        pommes->head = nouvellePomme;
        ChoisirCouleurDessin(couleurPommes);
        RemplirArc(nouvellePomme->position.x * TAILLE_CASE, nouvellePomme->position.y * TAILLE_CASE,
                   TAILLE_CASE, TAILLE_CASE, 360, 360);
    }
}
void AjouterPomme(Pommes* pommes, int x, int y) {
    PommeNode* nouvellePomme = (PommeNode*)malloc(sizeof(PommeNode));
    if (nouvellePomme == NULL) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    nouvellePomme->position.x = x;
    nouvellePomme->position.y = y;
    nouvellePomme->next = pommes->head;
    pommes->head = nouvellePomme;
    pommes->nombre++;
}
void GenererNouvellePomme(Pommes* pommes) {
    couleur couleurPommes = CouleurParComposante(255, 0, 0);
    int newX = rand() % LARGEUR;
    int newY = rand() % HAUTEUR;
    // Assuming you have a function named AjouterPomme to add a new apple to the linked list.
    AjouterPomme(pommes, newX, newY);
    ChoisirCouleurDessin(couleurPommes);
    RemplirArc(newX * TAILLE_CASE, newY * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, 360, 360);
}
int CollisionAvecPommeSerpent(Position position, PommeNode* pommes) {
    PommeNode* current = pommes;
    while (current != NULL) {
        if (position.x == current->position.x && position.y == current->position.y) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
