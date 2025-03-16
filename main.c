#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Definitions.h"
#include "initialisation.h"
#include "Affichage.h"
#include "jeu.h"


int main()
{
    plein_ecran();

    /** DEFINITION DES DONNEES **/

    int tour=0;
    S_plateau plat;                                 //D�finit le plateau de jeu
    S_joueur liste_de_joueurs[NB_JOUEURS];          //D�finit un tableau de 4 joueurs
    S_reserve res;                                  //D�finit la r�serve
    S_fabrique choix_du_cercle;                     //D�finit un cercle fabrique qui sera utilis� lorsque le joueur devra choisir un cercle fabrique
    int couleur_tuile_choisie;                      //D�finit un entier qui sera utilis� lorsque le joueur devra choisir une couleur d'un cercle fabrique
    int nb_tuiles;                                  //D�finit un entier qui sera utilis� pour garder le nombre de tuiles qu'un joueur prend
    int numero_cercle;                              //Garde le num�ro du cercle fabrique choisi
    int fin_partie ;                                 //Va permettre de savoir si la partie est termin�e ou non
    int tuiles_jeu;                                 //Nb de tuiles encore en jeu (r�serve + cercles fabriques)
    int i;

    /** INITIALISATION DES DONNEES DE DEBUT DE PARTIE**/

    initialisation_joueur(liste_de_joueurs); //ici seul le joueur est initialis� car les autres donn�es sont initialis�es � chaque tour
    mpc(&plat);                              //On initialise le mur qui sert de mod�le

    /** ALGORITHME PRINCIPAL DU JEU **/

    do
    {
        initialisation_reserve(&res);
        initialisation_pioche(&plat);
        melanger(&plat);                    //On initialise la r�serve et la pioche qu'on m�lange
        tuiles_dans_fabriques(&plat);       //On place les tuiles dans les 9 cercles fabriques

        tuiles_jeu = nb_tuiles_restantes(plat,res);

        while(tuiles_jeu!=0)
        {
            afficher_tout(plat,liste_de_joueurs,res,(tour%4)+1);                                                //On affiche toutes les donne�s du jeu

            choix_du_cercle = choix_fabrique(plat,&res,&numero_cercle,liste_de_joueurs,tour%4);             //On demande au joueur un cercle fabrique (ou la r�serve)
            printf("\n");
            couleur_tuile_choisie = choix_couleur(choix_du_cercle,res);                                     //On demande au joueur la couleur d'une tuile pr�sente dans le cercle choisi (ou la r�serve)
            printf("\n");
            nb_tuiles = nb_tuiles_cercle(choix_du_cercle,couleur_tuile_choisie,res);                        //On regarde le nombre de tuile qu'un joueur prend selon la couleur et le cercle choisi

            cercle_vide(&plat, &res, couleur_tuile_choisie,numero_cercle,nb_tuiles);                        //On vide le cercle choisi par le joueur (ou on vide une couleur de la r�serve)
            tuiles_dans_lignes(nb_tuiles,couleur_tuile_choisie,liste_de_joueurs,tour%4,plat);        //On place les tuiles choisies dans la ligne motif choisie par le joueur


            tuiles_jeu = nb_tuiles_restantes(plat,res);
            tour++;
        }

        tour=premier_joueur(liste_de_joueurs);  //Le joueur qui a la tuile -1 sera le premier � jouer le tour suivant

        for(i=0;i<NB_JOUEURS;i++)
        {
            place_sur_mur(liste_de_joueurs,i,plat);
            bonus(liste_de_joueurs,i,plat);
            penalite_vide(liste_de_joueurs,i);
        }


        fin_partie = detecte_dernier_tour(liste_de_joueurs);    //On regarde si c'est le dernier tour ou non

    }while(fin_partie==0);

    afficher_gagnant(liste_de_joueurs);         //On affiche le gagnant

}
