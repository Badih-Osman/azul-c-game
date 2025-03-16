#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Definitions.h"
#include "Affichage.h"
#include "jeu.h"


S_fabrique choix_fabrique(S_plateau jeu, S_reserve* restante, int* numero, S_joueur player[], int tour) //Choix d'un cercle fabrique ou de la réserve
{
    int choix,j,m;
    S_fabrique choix_joueur;

    if(restante->tuiles_reserve>0)
    {

        do
        {

            printf("Choisissez un cercle fabrique non-vide (1 %c 9) ou 0 pour la r%cserve : ",133,130);
            scanf("%d",&choix);
            if(choix==0)
            {
                m=1;
            }
            else
            {
                m=jeu.fabriques[choix-1].nb_tuiles_restantes;
            }

        }
        while(choix>9 || choix<0 || m==0 );
    }
    else
    {
        do
        {
            printf("Choisissez un cercle fabrique non-vide (1 %c 9) : ",133);
            scanf("%d",&choix);


        }
        while(choix>9 || jeu.fabriques[choix-1].tuiles[0]==0 || choix<1);
    }

    printf("\n");

    if(choix>0)
    {
        printf("Vous avez choisi le cercle %d :",choix);

        for(j=0; j<TAILLE_FABRIQUE; j++)
        {
            switch(jeu.fabriques[choix-1].tuiles[j])
            {
            case 1:
                color(15,9);    //Bleu
                printf(" ");
                break;
            case 2:
                color(15,4);    //Rouge
                printf(" ");
                break;
            case 3:
                color(15,6);    //Orange -> ici violet
                printf(" ");
                break;
            case 4:
                color(15,10);    //Noir -> ici gris
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

        choix_joueur = jeu.fabriques[choix-1];
        *numero=choix;
        return choix_joueur;

    }
    else    //Si la réserve est choisie
    {

        printf("Vous avez choisi la r%cserve : ",130);
        afficher_reserve(*restante);
        if(restante->tuile_penalite==0)     //Si un joueur a déjà pris dans la réserve
        {
            choix_joueur.tuiles[0] = 0;
            return choix_joueur;
        }
        else                                //Si c'est la première fois que quelqu'un prend dans la réserve
        {
            choix_joueur.tuiles[0] = 0;
            player[tour].penalite.tab_penalite[player[tour].penalite.nb_tuiles_penalite]=-1;
            player[tour].penalite.nb_tuiles_penalite++;
            restante->tuile_penalite=0;
            return choix_joueur;
        }
    }
    printf("\n");
}

int detecte_dernier_tour(S_joueur player[])   // return 1 si la partie est fini 0 si non
{

    int compteur,tour;
    int i,j;
    for(tour=0; tour<NB_JOUEURS; tour++)
    {

        for (i=0; i<5; i++)
        {
            compteur = 0;
            for (j=0; j<5; j++)
            {
                if (player[tour].mur.tuiles[i][j] != 0)
                {
                    compteur++;
                }
            }
            if (compteur == 5)
            {
                return 1;
                break;
            }
        }
    }
    return 0;
}


void place_sur_mur(S_joueur player[],int tour, S_plateau plateau)   //Place les tuiles de la ligne motif vers le mur + calcul du score
{

    int i,j,k,m,malus,ind;
    int ligne,col;
    for (ind=0; ind<5; ind++)
    {
        if ((ind+1) == player[tour].motif[ind][1])
        {



            for (j=0; j<5; j++)
            {
                if (plateau.mur_position_couler[ind][j] ==  player[tour].motif[ind][0])
                {
                    col = j;
                    break;
                }
            }
            player[tour].mur.tuiles[ind][col] = player[tour].motif[ind][0];
            player[tour].mur.nb_tuiles_placees++;
            player[tour].motif[ind][0] = 0;   // initialiser a zero apres avoir place sur le mur
            player[tour].motif[ind][1]= 0;


            ligne=ind;



            int cpt,score_lin,score_col;
            cpt=0;
            score_lin=0;

            for(j=0; j<TAILLE_MUR; j++)
            {
                if(player[tour].mur.tuiles[ligne][j]!=0)
                {
                    cpt++;
                }

                if(cpt==0)
                {
                    score_lin=0;
                }
                if(cpt==1)
                {
                    score_lin++;
                }
                if(cpt==2)
                {
                    for(k=0; k<TAILLE_MUR-1; k++)
                    {
                        if(player[tour].mur.tuiles[ligne][k]!=0 && player[tour].mur.tuiles[ligne][k+1]!=0)
                        {
                            score_lin=score_lin+2;
                        }
                        else
                        {
                            score_lin++;
                        }
                    }
                }
                if(cpt==3)
                {
                    for(k=0; k<TAILLE_MUR-2; k++)
                    {
                        if(player[tour].mur.tuiles[ligne][k]!=0 && player[tour].mur.tuiles[ligne][k+1]!=0 && player[tour].mur.tuiles[ligne][k+2]!=0)
                        {
                            score_lin=score_lin+3;
                        }
                        else if(player[tour].mur.tuiles[ligne][k]!=0 && player[tour].mur.tuiles[ligne][k+1]!=0)
                        {
                            score_lin=score_lin+2;
                        }
                        else
                        {
                            score_lin++;
                        }

                    }
                }
                if(cpt==4)
                {
                    for(k=0; k<TAILLE_MUR; k++)
                    {
                        if(player[tour].mur.tuiles[ligne][0]==0 || player[tour].mur.tuiles[ligne][TAILLE_MUR]==0)
                        {
                            score_lin=score_lin+4;
                        }
                        else
                        {


                            for(m=0; m<TAILLE_MUR-2; m++)
                            {
                                if(player[tour].mur.tuiles[ligne][m]!=0 && player[tour].mur.tuiles[ligne][m+1]!=0 && player[tour].mur.tuiles[ligne][m+2]!=0)
                                {
                                    score_lin=score_lin+3;
                                }
                                else if(player[tour].mur.tuiles[ligne][m]!=0 && player[tour].mur.tuiles[ligne][m+1]!=0)
                                {
                                    score_lin=score_lin+2;
                                }
                                else
                                {
                                    score_lin++;
                                }



                            }
                        }
                    }
                }
                if(cpt==5)
                {
                    score_lin=score_lin+5;
                }

                cpt=0;
                player[tour].score=player[tour].score+score_lin;
            }
            score_col=0;

            for(i=0; i<TAILLE_MUR; i++)
            {
                if(player[tour].mur.tuiles[i][col]!=0)
                {
                    cpt++;
                }
                if(cpt==0)
                {
                    score_col=0;
                }
                if(cpt==1)
                {
                    score_col=0;
                }
                if(cpt==2)
                {
                    for(i=0; i<TAILLE_MUR-1; i++)
                    {
                        if(player[tour].mur.tuiles[i][col]!=0 && player[tour].mur.tuiles[i+1][col]!=0)
                        {
                            score_col=score_col+2;
                        }
                        else
                        {
                            score_col++;
                        }
                    }
                }
                if(cpt==3)
                {
                    for(i=0; i<TAILLE_MUR-2; i++)
                    {
                        if(player[tour].mur.tuiles[i][col]!=0 && player[tour].mur.tuiles[i+1][col]!=0 && player[tour].mur.tuiles[i+2][col]!=0)
                        {
                            score_col=score_col+3;
                        }
                        else if(player[tour].mur.tuiles[i][col]!=0 && player[tour].mur.tuiles[i+1][col]!=0)
                        {
                            score_col=score_col+2;
                        }
                        else
                        {
                            score_col++;
                        }

                    }
                }
                if(cpt==4)
                {
                    for(i=0; i<TAILLE_MUR; i++)
                    {
                        if(player[tour].mur.tuiles[0][col]==0 || player[tour].mur.tuiles[TAILLE_MUR][col]==0)
                        {
                            score_col=score_col+4;
                        }
                        else
                        {


                            for(i=0; i<TAILLE_MUR-2; i++)
                            {
                                if(player[tour].mur.tuiles[i][col]!=0 && player[tour].mur.tuiles[i+1][col]!=0 && player[tour].mur.tuiles[i+2][col]!=0)
                                {
                                    score_col=score_col+3;
                                }
                                else if(player[tour].mur.tuiles[i][col]!=0 && player[tour].mur.tuiles[i+1][col]!=0)
                                {
                                    score_col=score_col+2;
                                }
                                else
                                {
                                    score_col++;
                                }



                            }
                        }
                    }
                }
                if(cpt==5)
                {
                    score_col=score_col+5;
                }

                cpt=0;
                player[tour].score=player[tour].score+score_col;
            }


        }
    }

    switch(player[tour].penalite.nb_tuiles_penalite)
    {
    case 0 :
        malus = 0;
        break;
    case 1 :
        malus = -1;
        break;
    case 2 :
        malus = -2;
        break;
    case 3 :
        malus = -4;
        break;
    case 4 :
        malus = -6;
        break;
    case 5 :
        malus = -8;
        break;
    case 6 :
        malus = -11;
        break;
    case 7 :
        malus = -14;
        break;
    }


    player[tour].score=player[tour].score+malus;

}



void bonus(S_joueur player[],int tour,S_plateau plateau)        //Ajoute au score les bonus (ligne/colonne/couleur complète)
{


    int i,j,compteur_b,compteur_r,compteur_j,compteur_v,compteur_bl,bon_lin,bon_col,bon_cou,compteur;
    int bonus;

    bon_lin=0;
    bon_col=0;
    bon_cou=0;
    compteur_b=0;
    compteur_bl=0;
    compteur_j=0;
    compteur_r=0;
    compteur_v=0;


    for (i=0; i<TAILLE_MUR; i++)
    {
        compteur = 0;

        for (j=0; j<TAILLE_MUR; j++)
        {
            if (player[tour].mur.tuiles[i][j] != 0)
            {
                compteur++;
            }
        }
        if (compteur == 5)
        {
            bon_lin=bon_lin+2;
        }
    }

    for(j=0; j<TAILLE_MUR; j++)
    {
        compteur=0;

        for(i=0; i<TAILLE_MUR; i++)
        {
            if(player[tour].mur.tuiles[i][j]!=0)
            {
                compteur++;
            }
        }
        if(compteur == 5)
        {
            bon_col=bon_col+7;
        }
    }


    for(i=0; i<TAILLE_MUR; i++)
    {
        for(j=0; j<TAILLE_MUR; j++)
        {
            switch(player[tour].mur.tuiles[i][j])
            {
            case 1 :
                compteur_b++;
                break;
            case 2 :
                compteur_r++;
                break;
            case 3 :
                compteur_j++;
                break;
            case 4 :
                compteur_v++;
                break;
            case 5 :
                compteur_bl++;
                break;
            }
        }
    }


    if(compteur_b == 5)
    {
        bon_cou=bon_cou+10;
    }

    if(compteur_r == 5)
    {
        bon_cou=bon_cou+10;
    }

    if(compteur_j == 5)
    {
        bon_cou=bon_cou+10;
    }

    if(compteur_v == 5)
    {
        bon_cou=bon_cou+10;
    }

    if(compteur_bl == 5)
    {
        bon_cou=bon_cou+10;
    }

    bonus=bon_lin+bon_col+bon_cou;

    player[tour].score= player[tour].score+bonus;
}


int choix_couleur(S_fabrique cercle, S_reserve restante)        //Le joueur choisi une couleur présente dans le cercle qu'il a choisi (ou la réserve)
{
    int couleur,i,compt=0;
    if(cercle.tuiles[0]!=0)     //Si un cercle est choisi
    {


        printf("\n");
        printf("Choisissez une couleur pr%csente dans le cercle (1 : bleu, 2 : rouge, 3 : Jaune, 4 : Vert, 5 : Blanc)  : ",130);
        scanf("%d",&couleur);

        for(i=0; i<4; i++)      //Permet de savoir si cette couleur est dans le cercle
        {
            if(cercle.tuiles[i]==couleur)
            {
                compt=compt+1;
            }
        }

        while(compt==0)     //Si la couleur n'est pas dans le cercle : redemander au joueur
        {
            printf("Choisissez une couleur pr%csente dans le cercle (1 : bleu, 2 : rouge, 3 : Jaune, 4 : Vert, 5 : Blanc)  : ",130);
            scanf("%d",&couleur);

            for(i=0; i<4; i++)
            {
                if(cercle.tuiles[i]==couleur)
                {
                    compt=compt+1;
                }
            }
        }

        printf("\n");
        switch(couleur)
        {
        case 1:
            printf("Vous avez choisi la couleur : bleu ");
            color(15,9);    //Bleu
            printf(" ");
            break;
        case 2:
            printf("Vous avez choisi la couleur : rouge ");
            color(15,4);    //Rouge
            printf(" ");
            break;
        case 3:
            printf("Vous avez choisi la couleur : jaune  ");
            color(15,6);    //Orange -> ici violet
            printf(" ");
            break;
        case 4:
            printf("Vous avez choisi la couleur : vert ");
            color(15,10);    //Noir -> ici gris
            printf(" ");
            break;
        case 5:
            printf("Vous avez choisi la couleur : blanc ");
            color(15,15);    //Blanc
            printf(" ");
            break;

        }

        color(15,0);
        return couleur;
    }
    else            //Si la réserve est choisie
    {

        printf("\nChoisissez une couleur pr%csente dans la r%cserve (1 : bleu, 2 : rouge, 3 : Jaune, 4 : Vert, 5 : Blanc)  : ",130,130);
        scanf("%d",&couleur);


        while(restante.reserve[couleur-1][1]==0 || couleur>5 || couleur<1)
        {
            printf("Choisissez une couleur pr%csente dans le cercle (1 : bleu, 2 : rouge, 3 : Jaune, 4 : Vert, 5 : Blanc)  : ",130);
            scanf("%d",&couleur);

        }


        switch(couleur)
        {
        case 1:
            printf("Vous avez choisi la couleur : bleu ");
            color(15,9);    //Bleu
            printf(" ");
            break;
        case 2:
            printf("Vous avez choisi la couleur : rouge ");
            color(15,4);    //Rouge
            printf(" ");
            break;
        case 3:
            printf("Vous avez choisi la couleur : jaune  ");
            color(15,6);    //Orange -> ici violet
            printf(" ");
            break;
        case 4:
            printf("Vous avez choisi la couleur : vert ");
            color(15,10);    //Noir -> ici gris
            printf(" ");
            break;
        case 5:
            printf("Vous avez choisi la couleur : blanc ");
            color(15,15);    //Blanc
            printf(" ");
            break;

        }
        color(15,0);
        return couleur;
    }
}

int nb_tuiles_cercle(S_fabrique cercle, int couleur, S_reserve restante)    //Compte le nombre de tuiles d'une couleur-dite dans un cercle
{
    int i,compt=0;
    if(cercle.tuiles[0]!=0)     //Si un cercle est chois
    {
        for(i=0; i<4; i++)
        {
            if(cercle.tuiles[i]==couleur)
            {
                compt=compt+1;
            }
        }
        printf("\nNb de tuiles : %d \n\n",compt);
        return compt;
    }
    else                        //Si la réserve est choisie
    {
        printf("\nNb de tuiles : %d \n\n",restante.reserve[couleur-1][1]);
        return restante.reserve[couleur-1][1];
    }
}


void cercle_vide(S_plateau* plat, S_reserve* restante, int couleur, int numero_cercle, int nb_tuiles)   //Vide un cercle après avoir été choisi
{
    int i,coul;
    if(plat->fabriques[numero_cercle-1].tuiles[0]!=0)   //Si le joueur a choisi un cercle fabrique
    {
        for(i=0; i<4; i++)
        {
            if(plat->fabriques[numero_cercle-1].tuiles[i]==couleur) //Si c'est la couleur choisie par le joueur -> remplacé par 0 dans le cercle
            {
                plat->fabriques[numero_cercle-1].tuiles[i]=0;
            }
            else                                                    // Si c'est une autre couleur :
            {
                coul=plat->fabriques[numero_cercle-1].tuiles[i];
                restante->reserve[coul-1][1]++;                     //on place cette couleur dans la réserve
                restante->tuiles_reserve++;
                plat->fabriques[numero_cercle-1].tuiles[i]=0;       //on remplace par 0 dans le cercle
            }
        }
        plat->fabriques[numero_cercle-1].nb_tuiles_restantes=0;
    }
    else                                                // Si un joueur a choisi la réserve
    {
        restante->reserve[couleur-1][1]=0;              //Il n'y a plus aucune tuile de cette couleur dans la réserve
        restante->tuiles_reserve=restante->tuiles_reserve - nb_tuiles;
    }
}


void tuiles_dans_lignes(int nb_tuiles, int couleur, S_joueur player[], int tour, S_plateau plateau)     //Choix d'une ligne motif où le joueur veut placer ses tuiles
{
    int choix=-1,i,compt,j,k,max,depart;


    while(choix==-1)
    {
        printf("Choisissez une ligne o%c placer vos tuiles (1 %c 5 ou 0 pour une penalit%c) : ",151,133,130);
        scanf("%d",&choix);
        if(choix<0 || choix>5)
        {
            choix=-1;
        }
        else
        {


            if(choix==0)        // Si le joueur choisit la pénalité
            {
                max=player[tour].penalite.nb_tuiles_penalite;
                for(j=max; j<max+nb_tuiles; j++)
                {
                    player[tour].penalite.tab_penalite[j]=couleur;
                    player[tour].penalite.nb_tuiles_penalite++;
                }
            }
            else                // Si le joueur choisit une ligne motif
            {


                if(player[tour].motif[choix-1][0]!=couleur && player[tour].motif[choix-1][0]!=0)    //Impossible : si une autre couleur est déjà présente sur la ligne
                {
                    choix=-1;
                }
                else
                {
                    if(player[tour].motif[choix-1][0]==0)       //Si la ligne est vide
                    {
                        for(i=0; i<5; i++)
                        {
                            if(plateau.mur_position_couler[choix-1][i]==couleur)    //donne la position de la couleur sur le modèle
                            {
                                compt=i;
                            }
                        }
                        if(player[tour].mur.tuiles[choix-1][compt]!=0)          //Si le joueur a délà cette couleur dans son mur sur cette ligne : impossible
                        {
                            choix=-1;
                        }
                        else
                        {
                            if(choix<nb_tuiles)     // Si le nombre de tuiles que l'on veut placer est supérieur au nombre de place disponible sur la ligne
                            {
                                player[tour].motif[choix-1][0]=couleur;
                                player[tour].motif[choix-1][1]=choix;
                                max=player[tour].penalite.nb_tuiles_penalite;
                                for(k=(max); k<(max+nb_tuiles-choix); k++)
                                {
                                    player[tour].penalite.tab_penalite[k]=couleur;
                                    player[tour].penalite.nb_tuiles_penalite++;
                                }
                            }
                            else                    // S'il y a assez de place pour placer les tuiles sur la ligne choisie
                            {
                                player[tour].motif[choix-1][0]=couleur;
                                player[tour].motif[choix-1][1]=nb_tuiles;
                            }

                        }
                    }

                    else        // Si la ligne n'est pas vide
                    {
                        if(choix==player[tour].motif[choix-1][1])    // Si la ligne est pleine
                        {
                            choix=-1;
                        }
                        else                                         //Si la ligne n'est ni vide ni pleine
                        {
                            if(choix-(player[tour].motif[choix-1][1])<nb_tuiles && choix-(player[tour].motif[choix-1][1]!=0))                                    //Si il y a assez de place pour placer toutes les tuiles
                            {
                                depart=player[tour].motif[choix-1][1];
                                player[tour].motif[choix-1][1]=choix;
                                max=player[tour].penalite.nb_tuiles_penalite;
                                for(k=(max); k<(max+nb_tuiles-choix+depart); k++)
                                {
                                    player[tour].penalite.tab_penalite[k]=couleur;
                                    player[tour].penalite.nb_tuiles_penalite++;
                                }
                            }
                            else
                            {
                                player[tour].motif[choix-1][1]=player[tour].motif[choix-1][1]+nb_tuiles;
                            }



                        }
                    }
                }

            }
        }
    }
}


int nb_tuiles_restantes(S_plateau plateau, S_reserve restante)      //Donne le nombre de tuiles en jeu (dans les cercles + la réserve)
{
    int total=0;
    int i;

    for(i=0; i<NB_FABRIQUES; i++)
    {
        total = total + plateau.fabriques[i].nb_tuiles_restantes;
    }
    total=total+restante.tuiles_reserve;

    return total;

}

void penalite_vide(S_joueur player[], int tour)             //Vide la ligne pénalité d'un joueur
{
    int i;
    for(i=0;i<7;i++)
    {
        player[tour].penalite.tab_penalite[i]=0;
    }
    player[tour].penalite.nb_tuiles_penalite=0;
}

int premier_joueur(S_joueur player[])                       //Permet au joueur qui a la tuile -1 d'être le premier à jouer le tour suivant
{
    int i,j,compt;
    for(i=0;i<NB_JOUEURS;i++)
    {
        if(player[i].penalite.nb_tuiles_penalite>0)
        {

            for(j=0;j<player[i].penalite.nb_tuiles_penalite;j++)
            {
                if(player[i].penalite.tab_penalite[j]==-1)
                {
                    compt=i;
                }
            }
        }
    }

    return compt;
}


