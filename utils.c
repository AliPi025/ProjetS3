/// \file utils.c
/// \brief fichier de fonctions utilitaires
/// \author Pierre ALIBERT
/// \date november 2021
#include "global.h"

/// \fn affiche un message d'erreur
void erreur(char *message){
    /// \param[in] message une phrase expliquant l'erreur  
    printf("%s", message);
} 

/// \fn crée un tableau
int * creer_tab_int(int dim){
    /// \param[in] dim une taille de tableau
    int tab[dim];
    return &tab;
}

/// \fn crée une matrice
int ** creer_mat_int(int nbRows,int nbCol){
    /// \param[in] nbRows un nombre de ligne
    /// \param[in] nbCol un nombre de colonne
    int tab[nbRows][nbCol];
    return &tab;
}

// void affiche_tab_int(int *tab,int dim, FILE *outfp);
//
/// \fn crée une matrice dynamique d'entiers
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol){
    /// \param[in] stTab une structure de matrice dynamique d'entiers
    /// \param[in] nbRows un nombre de ligne
    /// \param[in] nbCol un nombre de colonne
    (*stTab).tab = creer_mat_int(nbRows, nbCol);
    (*stTab).nbRows = nbRows;
    (*stTab).nbCol = nbCol;
}

/// \fn crée un tableau dynamique
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim){
    /// \param[in] stTab une structure de tableau dynamique
    /// \param[in] dim une taille de tableau
    (*stTab).tab = creer_tab_int(dim);
    (*stTab).dim = dim;
}

void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots); /// \fn crée une matrice dynamique de mots
/// \param[in] s_tabmots une structure de tableau dynamique de mots
// void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *outfp);
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp); /// \fn affiche une matrice de mots
/// \param[in] t_tabmots une structure de tableau dynamique de mots
/// \param[in] outfp un fichier de sortie de la fonction
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp); /// \fn affiche une matrice d'entiers
/// \param[in] t_tab une structure de tableau dynamique d'entiers
/// \param[in] outfp un fichier de sortie de la fonction
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp); /// \fn affiche une matrice de duels
/// \param[in] duels_mat une matrice contenant les duels
/// \param[in] nbRows un nombre de ligne
/// \param[in] nbCol un nombre de colonne
/// \param[in] outfp un fichier de sortie de la fonction
void init_tab_int(int *tab,int dim,int valeur); /// \fn initialise un tableau d'entiers avec une même valeur dans chaque case
/// \param[in] tab un tableau d'entiers
/// \param[in] dim une taille de tableau
/// \param[in] valeur un nombre entier
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur); /// \fn initialise une matrice d'entiers avec une même valeur dans chaque case
/// \param[in] mat une matrice d'entiers
/// \param[in] nbRows un nombre de ligne
/// \param[in] nbCol un nombre de colonne
/// \param[in] valeur un nombre entier
int min_borne(char * tab[],int dim,int borne);
int max_tab_indice(int *tab, int dim);
int min_tab_indice_non_j(int *tab, int dim,int j);
int som_tab_indice(int *tab, int dim);