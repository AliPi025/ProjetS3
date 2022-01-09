/// \brief Fonctions pour les votes de Condorcet
/// \file condorcet.c
/// \author Pierre ALIBERT
/// \date Décembre 2021
#include "global.h"

/// \fn Effectue un vote minimax
void minimax(int iord, liste larcs, t_mat_char_star_dyn tabmots,int nbCand,FILE *outfp){
    /// \param[in] iord Informe du type de fichier csv (ballots ou duels)
    /// \param[in] larcs Une structure de liste d'éléments
    /// \param[in] tabmots Une structure de matrice dynamique de mots 
    /// \param[in] nbCandidats Nombre de candidats
    /// \param[in] outfp Un fichier de sortie de la fonction
    int mintab[nbCand];
    init_tab_int(mintab, nbCand, 0);
    for(int i = 0; i<nbCand; i++){
        int nb_duels = nbCand - 1, j = 0;
        while(nb_duels > 0 && j < larcs.nbElt){
            Elementliste elt;
            pickEltList(larcs, &elt, j);
            if(elt.orig == i && mintab[i] > elt.poids){
                mintab[i] = elt.poids;
                nb_duels--;
            }
            j++;
        }
    }
    int maxvote = 0, imax = 0;
    for(int i = 0; i<nbCand; i++){
        if(mintab[i] > maxvote){
            maxvote = mintab[i];
            imax = i;
        }
    }
    affiche_resultat(outfp, "Condorcet minimax", nbCandidats, nbVotants, -1, tabmots.tab[0][4-4*iord+imax]);
}

/// \fn Effectue un vote de schulze
void schulze(int iord, liste larcs, t_mat_char_star_dyn tabmots,FILE *outfp){
    /// \param[in] iord Informe du type de fichier csv (ballots ou duels)
    /// \param[in] larcs Une structure de liste d'éléments
    /// \param[in] tabmots Une structure de matrice dynamique de mots 
    /// \param[in] outfp Un fichier de sortie de la fonction
    int vainqueur = -1;
    while(vainqueur == -1 && !emptyList(larcs)){
        bubbleSortList(&larcs);
        delFrontList(&larcs);
        vainqueur = vainqueurCondorcet(larcs, nbCandidats);
    }
    affiche_resultat(outfp, "Condorcet Schulze", nbCandidats, nbVotants, -1, tabmots.tab[0][4-4*iord + vainqueur]);
}

/// \fn Effectue un vote de Condorcet
int vainqueurCondorcet(liste larcs, int nbCand){
    /// \param[in] larcs Une structure de liste d'éléments
    /// \param[in] nbCand Nombre de candidats
    int vainqueur = -1;
    for(int i = 0; i<nbCand; i++){
        int nb_duels = nbCand - 1, j = 0;
        while(nb_duels > 0 && j < larcs.nbElt){
            Elementliste elt;
            pickEltList(larcs, &elt, j);
            if(elt.orig == i){
                vainqueur = i;
                nb_duels--;
            }else if(elt.dest == i){
                vainqueur = -1;
                nb_duels = 0;
            }
            j++;
        }
        if(vainqueur != -1)
            return vainqueur;
    }
    return -1;
}

/// \fn Effectue un vote de Condorcet et finalise avec une autre méthode s'il n'y a pas de vainqueur
void min_sch(int iord, liste larcs, t_mat_char_star_dyn tabmots, char * methode, FILE *outfp){
    /// \param[in] iord Informe du type de fichier csv (ballots ou duels)
    /// \param[in] larcs Une structure de liste d'éléments
    /// \param[in] tabmots Une structure de matrice dynamique de mots
    /// \param[in] methode Nom de la méthode utilisée
    /// \param[in] outfp Un fichier de sortie de la fonction
    int vainqueur = vainqueurCondorcet(larcs, nbCandidats);
    if(vainqueur == -1){
        if(!strcmp(methode, "cm"))
            minimax(iord, larcs, tabmots,nbCandidats, outfp);
        else if(!strcmp(methode, "cs"))
            schulze(iord, larcs, tabmots, outfp);
        else if(!strcmp(methode, "all")){
            minimax(iord, larcs, tabmots, nbCandidats, outfp);
            schulze(iord, larcs, tabmots, outfp);
        }
    }else{
        char * nom_meth = "";
        if(!strcmp(methode, "cm"))
            nom_meth = "Condorcet minimax";
        else if(!strcmp(methode, "cs"))
            nom_meth = "Condorcet Schulze";
        else if(!strcmp(methode, "all")){
            affiche_resultat(outfp, "Condorcet minimax", nbCandidats, nbVotants, -1, tabmots.tab[0][4-4*iord+vainqueur]);
            nom_meth = "Condorcet Schulze";
        }
        affiche_resultat(outfp, nom_meth, nbCandidats, nbVotants, -1, tabmots.tab[0][4-4*iord+vainqueur]);
    }
}
