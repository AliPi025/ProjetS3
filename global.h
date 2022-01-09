/// \brief Répertorie les fonctions nécessaires à l'exécution du vote
/// \file global.h
/// \author Pierre ALIBERT
/// \date Novembre 2021
#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include "sha256.h"
#include "sha256_utils.h"

#define NB_BALISES 3 /// \def Nombre de balise maximum
#define NB_METHODES 5 /// \def Nombre de méthode de vote maximal
#define OPT_I 0 /// \def Constante correspondant à la balise i
#define OPT_D 1 /// \def Constante correspondant à la balise d
#define OPT_O 2 /// \def Constante correspondant à la balise o
#define OPT_M 3 /// \def Constante correspondant à la balise m
#define OPT_H -1 /// \def Constante correspondant à l'absence de balise
#define SUCCESS 1 /// \def Retour fonction si tout s'est correctement exécuté
#define ERR -2 /// \def Retour fonction si un problème est rencontré
#define SEPARATEUR ',' /// \def Caractère de séparation des fichiers csv traités
//
#define MAX 300 /// \def Longueur maximale de la ligne dans le fichier
#define MAXINT 1000 /// \def Entier max utile dans le programme
#define LONGMOTS 30 /// \def Longueur max d'une chaîne de caractères
#define NBCOLADM 4 /// \def Nombre de colonnes administratives avant la colonne du premier choix
#define KO -1  /// \def Pas bon ou vide
#define OK 0 /// \def Bon
#define NBMAXOPTIONS 3 /// \def Nombre d'options maximum en entrée
//
/// \struct Pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn{
  int * tab;
  int dim;
} t_tab_int_dyn;

/// \struct Pour encapsuler des matrices dynamiques d'entiers avec le nombre de ligne et de colonne.
typedef struct s_mat_dyn{
  int ** tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct Pour encapsuler des matrices dynamiques de mots avec le nombre de ligne et de colonne.
typedef struct s_mat_char_dyn{
  char *** tab;
  int nbRows;
  int nbCol;
  int offset;
} t_mat_char_star_dyn;

/// \struct Arc pour les graphes
typedef struct s_arc_p{ /// arc pondéré = arc de préférence
  int orig;
  int dest;
  int poids;
} t_arc_p;

#include "elementliste.h"
#include "liste.h"

int nbCandidats; /// \var Nombre de candidats
int nbVotants; /// \var Nombre de votants
int nbVotesNuls; /// \var Nombre de votes nuls

// interactions.c

void erreur(char *message);

void help();

int verifop(int i, int indice, int notbis, char * tab_balises[], char * balise, char * extension, int argc, char * argv[]);

int getop(char *tab_balises[], int argc, char *argv[]);

void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur);

//

// utils.c

int * creer_tab_int(int dim);

int ** creer_mat_int(int nbRows,int nbCol);

void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol);

void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim);

void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots, int nbRows, int nbCol);

void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp);

void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp);

void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp);

void init_tab_int(int tab[],int dim,int valeur);

void init_mat_int(int nbRows, int nbCol, int mat[][nbCol],int valeur);

//

// lecture_csv.c

void find_lc_file(int *ligne, int *colonne, char * filename);

void read_voting_file(int iord, char * filename, char * delimiteur, t_mat_char_star_dyn *t_tabmots);

//

// traitement.c

void code_votant(char * nom_votant,char code_v[]);

int char_to_int(char * mot);

void calc_votes_nuls(t_mat_char_star_dyn tabmots,t_tab_int_dyn *votes_nuls);

void liste_duels_candidats(liste *duels, t_mat_int_dyn duels_mat);

void construct_mat_d(int iord, t_mat_int_dyn *duels_mat, t_mat_char_star_dyn tabmots, t_tab_int_dyn votes_nuls);

void construct_data_struct(int iord, liste *duels_l, t_mat_int_dyn *mat_d, t_mat_char_star_dyn *tabmots, t_tab_int_dyn *t_v_nuls, FILE *outfp);

//

// uninominal.c

void uninominal(t_tab_int_dyn votes_nuls, int tab_candidats[],t_mat_char_star_dyn tabmots);

void uninominal_un_tour(t_tab_int_dyn first_array,t_mat_char_star_dyn tabmots,FILE *outfp);

void aff_uni2_final(t_mat_int_dyn duels_mat, int imax, int imax2, t_mat_char_star_dyn tabmots, FILE *outfp);

void uninominal_deux_tours(t_tab_int_dyn first_array,t_mat_int_dyn duels_mat,t_mat_char_star_dyn tabmots,FILE *outfp);

//

// condorcet.c

void minimax(int iord, liste larcs, t_mat_char_star_dyn tabmots,int nbSommets,FILE *outfp);

void schulze(int iord, liste larcs, t_mat_char_star_dyn tabmots,FILE *outfp);

int vainqueurCondorcet(liste larcs, int nbSommets);

void min_sch(int iord, liste larcs, t_mat_char_star_dyn tabmots, char * methode, FILE *outfp);

//

#endif

