/// \file global.h
/// \author Vincent Dugat
/// \date august 2018
#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define NB_BALISES 4 /// \def nombre de balise maximal
#define NB_METHODES 5 /// \def nombre de méthode de vote maximal
#define OPT_I 0 /// \def variable correspondant à la balise i
#define OPT_D 1 /// \def variable correspondant à la balise d
#define OPT_O 2 /// \def variable correspondant à la balise o
#define OPT_M 3 /// \def variable correspondant à la balise m
#define OPT_H -1 /// \def variable correspondant à l'absence de balise
#define SUCCESS 1 /// \def retour fonction si l'entrée utilisateur est correcte
#define ERR -2 /// \def retour fonction si l'entrée utilisateur est erronée


#define MAX 300 /// \def< longueur maximale de la ligne dans le fichier
#define MAXINT 1000 /// \def< entier max utile dans le programme
#define LONGMOTS 30 /// \def< longueur max d'une chaîne de caractères
#define NBCOLADM 3 /// \def< nb de colonnes administratives avant la colonne du premier choix
#define KO -1  /// \def< pas bon ou vide
#define OK 0 /// \def< bon
#define NBMAXOPTIONS 4 /// \def < ça parle en soi.
//
#define MIN(a,b) (((a)<(b))?(a):(b)) /// \def retourne la plus petite valeur
#define MAXI(a,b) (((a)>(b))?(a):(b)) /// \def retourne la plus grande valeur
//
/// \struct pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn{
  int * tab;
  int dim;
} t_tab_int_dyn;

typedef struct s_mat_dyn{
  int ** tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct idem avec des chaînes de cractères
typedef struct s_mat_char_dyn{
  char *** tab;
  int nbRows;
  int nbCol;
  int offset;
} t_mat_char_star_dyn;

/// \struct arc pour les graphes
typedef struct s_arc_p{ /// arc pondéré = arc de préférence
  int orig;
  int dest;
  int poids;
} t_arc_p;

#include "elementliste.h"
#include "liste.h"

extern int nbCandidats; /// \var nombre de candidats
extern int nbVotants; /// \var nombre de votants
extern int nbVotesNuls; /// \var nombre de votes nuls

void help(); /// \fn affiche les différentes entrées possibles du programme
int getop(char **tab_balises, int argc, char **argv); /// \fn récupère les paramètres en entrée
/// \param[in] tab_balises un tableau comportant les noms des balises
/// \param[in] argc un nombre de paramètres sur la ligne d'entrée 
/// \param[in] argv un tableau des paramètres de la ligne d'entrée
void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur); /// \fn affiche les résulats de vote
/// \param[in] outfp un fichier de sortie de la fonction
/// \param[in] scrutin un nom de méthode de scrutin
/// \param[in] nbCandidats un nombre de candidats
/// \param[in] nbVotants un nombre de votants
/// \param[in] score un nombre réel du score du vainqueur
/// \param[in] vainqueur le nom du vainqueur à l'élection

// // utils.c
void erreur(char *message); /// \fn affiche un message d'erreur
/// \param[in] message une phrase expliquant l'erreur
int * creer_tab_int(int dim); /// \fn crée un tableau
/// \param[in] dim une taille de tableau
int ** creer_mat_int(int nbRows,int nbCol); /// \fn crée une matrice
/// \param[in] nbRows un nombre de ligne
/// \param[in] nbCol un nombre de colonne
// void affiche_tab_int(int *tab,int dim, FILE *outfp);
//
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol); /// \fn crée une matrice dynamique d'entiers
/// \param[in] stTab une structure de matrice dynamique d'entiers
/// \param[in] nbRows un nombre de ligne
/// \param[in] nbCol un nombre de colonne
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim); /// \fn crée un tableau dynamique
/// \param[in] stTab une structure de tableau dynamique
/// \param[in] dim une taille de tableau
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
//
// lecture_fich_csv
void read_voting_file(char * filename,char *delimiteur,t_mat_char_star_dyn *t_tabmots); /// \fn convertit un fichier de vote sous forme de matrice dynamique
/// \param[in] filename le nom du fichier à convertir
/// \param[in] delimiteur caractère ou mot qui delimite les valeurs du fichier
/// \param[in] t_tabmots une structure de tableau dynamique de mots
//
// traitement.c
char * code_candidat(int code,t_mat_char_star_dyn tabmots); /// \fn cherche le code du candidat dans une matrice
/// \param[in] code entier correspondant au code d'un candidat
/// \param[in] tabmots une structure de tableau dynamique de mots
void scan_ligne(t_mat_char_star_dyn *tabmots,int ligne); /// \fn affiche une ligne d'une matrice
/// \param[in] tabmots une structure de tableau dynamique de mots
/// \param[in] ligne numero d'une ligne de la matrice
// void replace_value(char * tab[],int dim,int min,int cpt);
int construct_data_struct(t_mat_char_star_dyn *tabmots, t_tab_int_dyn *first_array,t_mat_int_dyn *duels_mat,FILE *outfp);
/// \param[in] tabmots une structure de tableau dynamique de mots
/// \param[in] first_array une structure de tableau dynamique
/// \param[in] duels_mat une structure de matrice dynamique d'entiers
/// \param[in] outfp un fichier de sortie de la fonction
void construct_mat_duels_d(t_mat_char_star_dyn tabmots,t_mat_int_dyn *duels_mat,int nbCandidats,FILE *outfp); /// \fn construit une matrice de duels
/// \param[in] tabmots une structure de tableau dynamique de mots
/// \param[in] duels_mat une structure de matrice dynamique d'entiers
/// \param[in] nbCandidats un nombre de candidats
/// \param[in] outfp un fichier de sortie de la fonction
//
// condorcet.c
void uninominal_un_tour(t_tab_int_dyn first_array,t_mat_char_star_dyn tabmots,FILE *outfp); /// \fn effectue un vote uninominal à un tour
/// \param[in] first_array une structure de tableau dynamique
/// \param[in] tabmots une structure de tableau dynamique de mots
/// \param[in] outfp un fichier de sortie de la fonction
void uninominal_deux_tours(t_tab_int_dyn first_array,t_mat_int_dyn duels_mat,t_mat_char_star_dyn tabmots,FILE *outfp); /// \fn effectue un vote uninominal à deux tours
/// \param[in] first_array une structure de tableau dynamique
/// \param[in] duels_mat une structure de matrice dynamique d'entiers
/// \param[in] tabmots une structure de tableau dynamique de mots
/// \param[in] outfp un fichier de sortie de la fonction
//int condorcet_paires(liste larcs,FILE *outfp);
//
// minimax
int minimax(liste larcs, int nbSommets,FILE *outfp); /// \fn renvoie le maximum des minimums
/// \param[in] larcs une liste des minimums
/// \param[in] nbSommets nombre de valeurs dans la liste
/// \param[in] outfp un fichier de sortie de la fonction
//
// utils_scrutins.c
int maxSommet(liste larcs); /// \fn renvoie la valeur maximum de la liste
/// \param[in] larcs une liste
//void scan_arcs(t_mat_int_dyn duels_mat,liste *larcs);
int trouveSuc(liste larcs,int sommet,int **tabVus);
bool dfs(liste larcs,int sommet,int * tabMark,int **tabVus);
int vainqueurCondorcet(liste larcs, int nbSommets); /// renvoie le vainqueur de condorcet
/// \param[in] larcs une liste
/// \param[in] nbSommets nombre de valeurs dans la liste
int scoreInt(int som,liste larcs);
//
int schulze(t_mat_int_dyn duels_mat,FILE *outfp); /// \fn effectue la méthode de Schulze
/// \param[in] duels_mat une structure de matrice dynamique d'entiers
/// \param[in] outfp un fichier de sortie de la fonction

#endif
