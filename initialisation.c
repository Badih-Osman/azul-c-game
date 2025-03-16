#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Definitions.h"
#include "initialisation.h"
#include "Affichage.h"
#include "jeu.h"



void initialisation_joueur(S_joueur player[])   //Initialisation des 4 joueurs
{
    int i,j,k,indent,m;
    char texte[50];
    for(indent=0; indent<NB_JOUEURS; indent++)
    {

        // intisialisation du pseudo du jouer
        printf("Pseudo joueur %d : ",indent+1);
        scanf("%s",texte);

        player[indent].pseudo=(char*)malloc((strlen(texte)+1)*sizeof(char));
        if(player[indent].pseudo!=NULL)
            strcpy(player[indent].pseudo,texte);

        // intisialisation du score du jouer
        player[indent].score = 0;

        for (i=0; i<TAILLE_MUR; i++)        //Init du mur à vide
        {
            for (j=0; j<TAILLE_MUR; j++)
            {
                player[indent].mur.tuiles[i][j] = 0;
            }
        }

        player[indent].mur.nb_tuiles_placees = 0;

        for (k=0; k<5; k++)                  //Init lignes motifs
        {
            player[indent].motif[k][0] = 0;        // pas de couleur choisi
            player[indent].motif[k][1] = 0;        // aucun piece dans cette ligne1


        }
        for(m=0;m<7;m++)
        {
            player[indent].penalite.tab_penalite[m]=0;
        }
        player[indent].penalite.nb_tuiles_penalite=0;
    }
}


void initialisation_pioche(S_plateau* plat)      //Rempli la pioche de 100 tuiles (20 de chaque couleur)
{
    int i;
    for (i=0; i<100; i++)
    {
        plat->tuiles_restantes[i] = 1 + (i/20);
    }
}


void melanger(S_plateau* plat)
{
    int i,j,temp;
    srand(time(NULL));
    for ( i = 0; i < 100; i++)
    {
        j = rand()%100;
        temp = plat->tuiles_restantes[j];
        plat->tuiles_restantes[j] = plat->tuiles_restantes[i];
        plat->tuiles_restantes[i] = temp;
    }
}

void tuiles_dans_fabriques(S_plateau* plat) //Place 4 tuiles dans chaque cercle fabrique
{
    int i,j;
    int compteur = 0;
    for (i=0; i<NB_FABRIQUES; i++)
    {
        for (j=0; j<TAILLE_FABRIQUE; j++){
            plat->fabriques[i].tuiles[j] = plat->tuiles_restantes[compteur];
            plat->tuiles_restantes[compteur]=0;
            compteur++;
        }
        plat->fabriques[i].nb_tuiles_restantes = 4; // 4 nouvelles pieces dans fabrique actuelle
     }
}


void mpc(S_plateau* plat) {             //Modèle pour le mur + la ligne pénalité

    int penalite_defini[7] = {-1, -1, -2, -2, -2, -3, -3};
    memcpy(plat->penalite_defini, penalite_defini, sizeof(penalite_defini));

    int mur_position_couler[5][5] = {{1, 3, 2, 4, 5},
                                     {5, 1, 3, 2, 4},
                                     {4, 5, 1, 3, 2},
                                     {2, 4, 5, 1, 3},
                                     {3, 2, 4, 5, 1}};
    memcpy(plat->mur_position_couler, mur_position_couler, sizeof(mur_position_couler));
}



void initialisation_reserve(S_reserve* res)     //Initialisation de la réserve
{
    int i,j;
    res->tuiles_reserve=0;
    for(j=0;j<5;j++)
    {
        res->reserve[j][0]=j+1;     //On met les 5 couleurs dans la colonne de gauche
    }
    for(i=0;i<5;i++)
    {
        res->reserve[i][1]=0;       //On met le nombre de tuile de chaque couleur à 0
    }
    res->tuile_penalite=1;          //La tuile premier joueur est dans la réserve
}
