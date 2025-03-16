#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#define NB_JOUEURS 4			//Seul le mode 4 joueurs est modélisé
#define NB_FABRIQUES 9		    //A 4 joueurs : 9 cercles fabriques
#define TAILLE_FABRIQUE 4		//Les fabriques peuvent contenir 4 tuiles max
#define TAILLE_MUR 5			//Le mur est composé de lignes de 5 tuiles


typedef struct fabrique{

    int tuiles[TAILLE_FABRIQUE]; 	// Tableau de tuiles de la fabrique, les tuiles étant définies par une couleur (1 : bleu, 2 : rouge, 3 : Orange, 4 : Noir, 5 : Blanc) / Aucune couleur n'est représenté par 0 car il est laissée pour les cases vides
    int nb_tuiles_restantes; 		// Nombre de tuiles restantes dans la fabrique : permet de savoir si une fabrique est vide ou non

}S_fabrique;


typedef struct mur{

    int tuiles[TAILLE_MUR][TAILLE_MUR]; 	// Tableau à 2 dimensions représentant les tuiles placées sur le mur (il contient les couleurs des tuiles placées)
    int nb_tuiles_placees; 	                // Nombre de tuiles placées sur le mur

}S_mur;


typedef struct penalite{

    int tab_penalite[7];
    int nb_tuiles_penalite;

}S_penalite;


typedef struct joueur{

    char *pseudo; 				    // Pseudo du joueur
    int score; 						// Score du joueur
    S_mur mur; 					    // Mur du joueur
    int motif[5][2];				//Lignes motifs du joueur avec dans la première colonne la couleur des tuiles placées et dans la 2ème colonne le nombre de tuiles
    S_penalite penalite;

}S_joueur;



typedef struct plateau{

    S_fabrique fabriques[NB_FABRIQUES]; 	// Représente les 9 fabriques du jeu
    int tuiles_restantes[100]; 			// Tuiles pas encore en jeu, qui sont dans la "pioche"
    int nb_tuiles_piochees;	                // Compteur du nombre de tuiles piochées
    int mur_position_couler[5][5];
    int penalite_defini[7];

}S_plateau;


typedef struct reserve{

    int reserve[5][2];
    int tuiles_reserve;
    int tuile_penalite;         // 1 si la réserve n'a pas encore été touché et 0 si un joueur a déjà pris dedans

}S_reserve;



#endif // DEFINITIONS_H_INCLUDED
