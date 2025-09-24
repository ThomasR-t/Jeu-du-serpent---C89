#include "graphique.h"
#include "serpent.h"
#include "pommes.h"
#include "obstacles.h"
#include <time.h>
void Attendre(unsigned int millisecondes) {
  clock_t start_time = clock();
  while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < millisecondes){
  }
}
void InitialiserJeu(Serpent* serpent, Pommes* pommes, Obstacles* obstacles) {
    serpent->longueur = 10;
    serpent->corps = malloc(sizeof(Position) * serpent->longueur);
    pommes->nombre = NOMBRE_POMMES;
    obstacles->nombre = NOMBRE_OBSTACLES;
    srand(time(NULL));
    serpent->corps[0].x = LARGEUR / 2 * TAILLE_CASE;
    serpent->corps[0].y = HAUTEUR / 2 * TAILLE_CASE;
    /* Initialisation des obstacles*/
    obstacles->positions = malloc(sizeof(Position) * obstacles->nombre);
    for (int i = 0; i < obstacles->nombre; i++) {
        obstacles->positions[i].x = rand() % LARGEUR;
        obstacles->positions[i].y = rand() % HAUTEUR;
    }
}
void AfficherSerpent(Serpent* serpent) {
    couleur couleurSerpent = CouleurParComposante(255, 255, 0);
    ChoisirCouleurDessin(couleurSerpent);
    for (int i = 0; i < serpent->longueur; i++) {
        RemplirRectangle(serpent->corps[i].x, serpent->corps[i].y, TAILLE_CASE, TAILLE_CASE);
    }
}
void LibererMemoire(Serpent* serpent, Pommes* pommes, Obstacles* obstacles) {
    free(serpent->corps);
    LibererPommes(pommes);
    free(obstacles->positions);
}
void Graphique() {
    InitialiserGraphique();
    CreerFenetre(0, 0, 1240, 940);
    EcrireTexte(500, 400, "Le jeu va commencer !", 2);
    Attendre(2000);
    EffacerEcran(CouleurParComposante(0, 0, 0));
}
void AffichageBasique() {
    ChoisirCouleurDessin(CouleurParComposante(111, 255, 94));
    RemplirRectangle(0, 0, 1140, 760);
}
void AfficherScore(int score) {
   char scoreText[20];
  snprintf(scoreText, 20, "Score: %d", score);
  ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
  RemplirRectangle(20, 820, 150, 40);
  ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
  EcrireTexte(20, 850, scoreText, 2);
}
void AfficheTemps(int minute, int seconde) {
   char temps[6];
  snprintf(temps, 6, "%02d:%02d", minute, seconde);
  ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
  RemplirRectangle(20, 870, 70, 40);
  ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
  EcrireTexte(20, 900, temps, 2);
}
void AfficherEcranFin(int score) {
  ChoisirCouleurDessin(CouleurParComposante(255,0,0));
    EcrireTexte(500, 300, "Game Over!", 2);
    
}
int PauseJeu(int perdu) {
    while (perdu != -1) {
        if (ToucheEnAttente()) {
            int touche = Touche();
            if (touche == XK_space) {
                return 1;  // La barre d'espace a été pressée, reprendre le jeu
            }
        }
        Attendre(100);
    }
}
