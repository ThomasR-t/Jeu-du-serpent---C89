#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include <graph.h>
#include "serpent.h"
#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR 40
#define LARGEUR 60
#define TAILLE_CASE 19
#define NOMBRE_POMMES 5
#define NOMBRE_OBSTACLES 10
#define CYCLE 100000L
void Attendre(unsigned int millisecondes);
void Graphique();
void AffichageBasique();
void AfficherScore(int score);
void AfficheTemps(int minute, int seconde);
void AfficherEcranFin(int score);
int PauseJeu(int perdu);
void AfficherSerpent(Serpent* serpent);
void InitialiserJeu(Serpent* serpent, Pommes* pommes, Obstacles* obstacles);
void LibererMemoire(Serpent* serpent, Pommes* pommes, Obstacles* obstacles);
#endif
