#include "serpent.h"
#include "pommes.h"
#include "obstacles.h"
#include "graphique.h"
#include <stdlib.h>
#include <stdio.h>
int main() {
    int direction = 1;
    unsigned long suivant = Microsecondes() + CYCLE;
    int temps[2] = {0, 0}, seconde_actuel, old_seconde;
    int jeuEnPause = 0, perdu = 0, score = 0;
    Serpent serpent;
    Pommes pommes;
    Obstacles obstacles;
    InitialiserJeu(&serpent, &pommes, &obstacles);
    Graphique();
    EffacerEcran(CouleurParComposante(0, 0, 0));
    AffichageBasique();
    GenererPommes(&pommes);
    GenererObstacles(&obstacles, &pommes, &serpent);
    AfficherSerpent(&serpent);
    AfficherScore(score);
    while (perdu != -1) {
        if (!jeuEnPause) {
            if (Microsecondes() > suivant) {
                suivant = Microsecondes() + CYCLE;
                seconde_actuel = (suivant / 1000000) % 10;
                if (seconde_actuel != old_seconde) {
                    old_seconde = seconde_actuel;
                    if ((temps[1] + 1) == 60) {
                        temps[0]++;
                        temps[1] = 0;
                    } else {
                        temps[1]++;
                    }
                    AfficheTemps(temps[0], temps[1]);
                }
            }
            if (ToucheEnAttente()) {
                int touche = Touche();
                int nouvelleDirection;
                // Déterminer la nouvelle direction en fonction de la touche pressée
                if (touche == XK_Right) {
                    nouvelleDirection = 1;
                } else if (touche == XK_Left) {
                    nouvelleDirection = 2;
                } else if (touche == XK_Up) {
                    nouvelleDirection = 3;
                } else if (touche == XK_Down) {
                    nouvelleDirection = 4;
                } else if (touche == XK_space) {
                    jeuEnPause = 1;
                } else if (touche == XK_Escape) {
                    return EXIT_FAILURE;
                }
                // Vérifier si la nouvelle direction n'est pas opposée à la direction actuelle
                if (!EstDirectionOpposee(direction, nouvelleDirection)) {
                    // Mettre à jour la direction du serpent
                    direction = nouvelleDirection;
                }
            }
            DeplacerSerpent(&serpent, &direction);
            perdu = GestionCollision(&serpent, &pommes, &obstacles, perdu, &score);
        } else {
            if (ToucheEnAttente()) {
                int touche = Touche();
                if (touche == XK_space) {
                    if (touche == XK_Escape) {
                        return EXIT_FAILURE;
                    }
                    jeuEnPause = 0;
                }
            }
        }
    }
    LibererMemoire(&serpent, &pommes, &obstacles);
    return EXIT_SUCCESS;
}
