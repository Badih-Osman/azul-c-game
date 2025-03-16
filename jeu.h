#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

S_fabrique choix_fabrique(S_plateau jeu, S_reserve* restante, int* numero, S_joueur player[], int tour);

int detecte_dernier_tour(S_joueur player[]);

void place_sur_mur(S_joueur player[],int tour, S_plateau plateau);

int nb_tuiles_cercle(S_fabrique cercle, int couleur, S_reserve restante);

int choix_couleur(S_fabrique cercle, S_reserve restante);

void cercle_vide(S_plateau* plat, S_reserve* restante, int couleur, int numero_cercle, int nb_tuiles);

void tuiles_dans_lignes(int nb_tuiles, int couleur, S_joueur player[], int tour, S_plateau plateau);

void bonus(S_joueur player[],int tour,S_plateau plateau);

int nb_tuiles_restantes(S_plateau plateau, S_reserve restante);

void penalite_vide(S_joueur player[], int tour);

int premier_joueur(S_joueur player[]);


#endif // JEU_H_INCLUDED
