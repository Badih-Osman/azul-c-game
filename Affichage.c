#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Definitions.h"
#include "initialisation.h"
#include "Affichage.h"
#include "jeu.h"



void plein_ecran()
{
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
}


void positionner_curseur(int ligne, int colonne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}


void color (int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
}
// 0.Noir
// 1.Bleu fonc
// 2.Vert fonc
// 3.Turquoise
// 4.Rouge fonc
// 5.Violet
// 6.Vert caca d'oie
// 7.Gris clair
// 8.Gris fonc
// 9.Bleu fluo
// 10.Vert fluo
// 11.Turquoise
// 12.Rouge fluo
// 13.Violet 2
// 14.Jaune
// 15.Blanc


void dessiner_rectangle(int ligne,int colonne,int c,int lg, int la)
{
    int i=0;
    int j=0;
    positionner_curseur(ligne, colonne);
    color (15, c);
    for(i=0; i<=lg; i++)
    {
        for(j=0; j<la; j++)
        {
            printf(" ");
        }
        positionner_curseur(ligne+i, colonne);

    }

}

void afficher_plateau(S_plateau jeu)    // Affichage des cercles fabriques
{
    int i,j;
    printf("\n");
    for(i=0; i<NB_FABRIQUES; i++)
    {
        printf("Cercle %d : | ",i+1);

        for(j=0; j<TAILLE_FABRIQUE; j++)
        {
            switch(jeu.fabriques[i].tuiles[j])
            {
            case 0:
                color(15,0);    //Noir
                printf(" ");
                break;
            case 1:
                color(15,3);    //Bleu
                printf(" ");
                break;
            case 2:
                color(15,4);    //Rouge
                printf(" ");
                break;
            case 3:
                color(15,6);    //Orange -> ici jaune
                printf(" ");
                break;
            case 4:
                color(15,10);    //Noir -> ici vert
                 printf(" ");
                break;
            case 5:
                color(15,15);    //Blanc
                printf(" ");
                break;

            }
            color(15,0);
            printf(" | ");

        }
        printf("\t\t\t\t");
        if ((i+1)%3==0) {
            printf("\n\n");
        }
    }
    printf("\n");

}


void afficher_joueur(S_joueur player[],int numero, S_plateau plat, int tour_de)   //Affichage données d'un seul joueur
{
    int i,j,c,l,m;
    color(15,0);

    for(i=0; i<5; i++)
    {
        for (int compenser=0; compenser<2;compenser++)
        {
            color(15,0);
            for(m=0; m<(5 - (i+1)); m++) {
                printf("    ");
            }

            for(j=0; j< (i+1) - player[numero + compenser].motif[i][1]; j++){
                printf("|   ");
            }

            switch(player[numero + compenser].motif[i][0])
            {
            case 1:
                color(15,3);    //Bleu
                c=3;
                break;
            case 2:
                color(15,4);    //Rouge
                c=4;
                break;
            case 3:
                color(15,6);    //Orange -> ici jaune
                c=6;
                break;
            case 4:
                color(15,10);    //Noir -> ici vert
                c=10;
                break;
            case 5:
                color(15,15);    //Blanc
                c=15;
                break;
            }

            for(j=0; j<player[numero + compenser].motif[i][1]; j++)
            {
                color(15,0);
                printf("| ");
                color(15,c);
                printf(" ");
                color(15,0);
                printf(" ");
            }
            color(15,0);
            printf("|  ->  | ");
             for(l=0; l<TAILLE_MUR; l++)
            {
                switch(player[numero + compenser].mur.tuiles[i][l])
                {
                case 1:
                    color(15,3);    //Bleu
                    c=3;
                    break;
                case 2:
                    color(15,4);    //Rouge
                    c=4;
                    break;
                case 3:
                    color(15,6);    //Orange -> ici jaune
                    c=6;
                    break;
                case 4:
                    color(15,10);    //Noir -> ici vert
                    c=10;
                    break;
                case 5:
                    color(15,15);    //Blanc
                    c=15;
                    break;
                }
                printf(" ");
                color(15,0);
                printf(" | ");
            }
           printf("\t\t\t");
        }
        printf("\n\n");
    }

    int joueur_couleur;
    for (int rep=0; rep<2;rep++)
    {
        switch(tour_de)
        {
        case 1:
            joueur_couleur=2;
            break;
        case 2:
            joueur_couleur=11;
            break;
        case 3:
            joueur_couleur=12;
            break;
        case 4:
            joueur_couleur=13;
            break;
        }

        color(15,0);
        printf("\tJoueur : ");
        color(joueur_couleur, 0);
        printf("%s", player[numero + rep].pseudo);
        color(15,0);
        printf("\t\t\t\t\t\t\t\t\t");
    }
    printf("\n");
}

void afficher_mur_complet(S_plateau plat, S_joueur players[], int tour_de){         //Affichage du mur

    printf("\n\n");

    for(int i=0; i<TAILLE_MUR; i++){

        printf("\t");
        switch(i){
            case 2:
                printf("  C'est le tour de:\t\t\t   ");
                break;
            case 3:
                color(8, 4);
                printf(" %-20.20s\t\t\t", players[tour_de - 1].pseudo);
                color(15,0);
                printf("   ");
                break;
            default:
                color(15,0);
                printf("\t\t\t\t\t   ");
        }



        for(int l=0; l<TAILLE_MUR; l++){
            switch(plat.mur_position_couler[i][l])
            {
            case 1:
                color(15,3);    //Bleu
                break;
            case 2:
                color(15,4);    //Rouge
                break;
            case 3:
                color(15,6);    //Orange -> ici jaune
                break;
            case 4:
                color(15,10);    //Noir -> ici vert
                break;
            case 5:
                color(15,15);    //Blanc
                break;
            }
            printf(" ");
            color(15,0);
            printf(" | ");
        }

        printf("\t\t\t");
        switch(i){
         case 1:
            printf ("--------------------");
            break;
        case 2:
            printf("| Score = %.8d |",players[tour_de - 1].score);
            break;
        case 3:
            printf("--------------------");
            break;
        }

            printf("\n\n");
        }
    printf("\n\n");
}


void afficher_penalite(S_plateau plat, S_joueur players[], int tour_de){            //Affichage de la ligne pénalité

    printf("\t");

    for(int j=0; j<2; j++){
        for(int i=0; i<7; i++){
            printf("%d ", plat.penalite_defini[i]);
        }
        printf("\t\t\t\t\t\t\t\t");
    }

    printf("\n\t");

    for(int j=0; j<2; j++){
        for(int i=0; i<7; i++){

            color(15,0);
            printf(" ");

            switch(players[tour_de + j].penalite.tab_penalite[i])
            {
            case -1:
                color(11,11);
                 break;
            case 1:
                color(15,3);    //Bleu
                break;
            case 2:
                color(15,4);    //Rouge
                break;
            case 3:
                color(15,6);    //Orange -> ici jaune
                break;
            case 4:
                color(15,10);    //Noir -> ici vert
                break;
            case 5:
                color(15,15);    //Blanc
                break;
            }

            printf(" ");
            color(15,0);
            printf(" ");
        }
        color(15,0);
        printf("\t\t\t\t\t\t\t\t");
    }

    printf("\n");

}


void afficher_tout(S_plateau plat, S_joueur players[], S_reserve res, int tour_de){ //Affichage de l'ensemble des données

     system("cls");

    afficher_plateau(plat);

    afficher_reserve(res);

    afficher_joueur(players,0, plat, tour_de);

    afficher_penalite(plat, players, 0);

    afficher_mur_complet(plat, players, tour_de);

    afficher_joueur(players,2, plat, tour_de);

    afficher_penalite(plat, players, 2);

}


void afficher_reserve(S_reserve restante)           //Affichage de la réserve
{
    int k,l,c;
    color(4, 15);
    printf("\t\t\t\t\t\t\t\tR%cserve :",130);
    color(15,0);
    printf(" ");
    if (restante.tuile_penalite == 1){
        color(7,0);
        printf("-1");
        color(15,0);
    }
    if(restante.tuiles_reserve==0)
    {
        printf(" Vide");
    }
    else
    {
        printf(" ");
        for(k=0; k<5; k++)
        {
            switch(restante.reserve[k][0])
            {
            case 1:
                color(15,9);    //Bleu
                c=9;
                break;
            case 2:
                color(15,4);    //Rouge
                c=4;
                break;
            case 3:
                color(15,6);    //jaune
                c=6;
                break;
            case 4:
                color(15,10);    //vert
                c=10;
                break;
            case 5:
                color(15,15);    //Blanc
                c=15;
                break;
            }

            for(l=0; l<restante.reserve[k][1]; l++)
            {
                color(15,c);
                printf(" ");
                color(15,0);
                printf(" | ");
            }
            color(15,0);

        }
    }

    printf("\n\n\n");
}



void afficher_gagnant(S_joueur player[])
{
    int i,max,compt;
    max=0;
    for(i=0;i<NB_JOUEURS;i++)
    {
        if(player[i].score>max)
        {
            max = player[i].score;
            compt=i;
        }
    }
    printf("\n--------------------------------------\n");
    printf("Le gagnant est %s avec %d points !",player[compt].pseudo,max);

}
