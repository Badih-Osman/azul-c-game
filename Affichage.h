#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void color (int couleurDuTexte, int couleurDuFond);

void afficher_plateau(S_plateau jeu);

void afficher_reserve(S_reserve restante);

void plein_ecran();

void afficher_joueur(S_joueur player[], int tour, S_plateau plat, int tour_de);

void dessiner_rectangle(int ligne,int colonne,int c,int lg, int la);

void positionner_curseur(int ligne, int colonne);

void afficher_penalite(S_plateau plat, S_joueur players[], int tour_de);

void afficher_tout(S_plateau plat, S_joueur players[], S_reserve res, int tour_de);

void afficher_mur_complet(S_plateau plat, S_joueur players[], int tour_de);

void afficher_gagnant(S_joueur player[]);

#endif // AFFICHAGE_H_INCLUDED
