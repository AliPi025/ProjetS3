/// \brief Rend traitable les informations contenus dans des fichiers csv
/// \file lecture_csv.c
/// \author Pierre ALIBERT
/// \date Décembre 2021
#include "global.h"

/// \fn Cherche le nombre de colonnes et lignes d'un fichier csv
void find_lc_file(int *ligne, int *colonne, char * filename){
    /// \param[in,out] ligne Récupère le nombre de ligne
    /// \param[in,out] ligne Récupère le nombre de colonne
    /// \param[in] filename Fichier csv à traiter
    FILE * fichiercsv;
    fichiercsv = fopen(filename, "r");
    char car;
    char lignefile[MAX];
    *ligne = 0;
    while(fgets(lignefile,1000,fichiercsv) != NULL){
        (*ligne)++;
    }
    rewind(fichiercsv);
    *colonne = 0;
    while((car = fgetc(fichiercsv)) != EOF){
        if(car == SEPARATEUR){
            (*colonne)++;
        }
    }
    (*colonne) = (*colonne)/(*ligne) + 1;
    fclose(fichiercsv);
}

/// \fn Rentre les informations d'un fichier csv dans une structure de matrice dynamique de mots
void read_voting_file(int iord, char * filename, char * delimiteur, t_mat_char_star_dyn *t_tabmots){
    /// \param[in] iord Informe du type de fichier csv (ballots ou duels)
    /// \param[in] filename Fichier csv à traiter
    /// \param[in] delimiteur Donne les différents séparateurs qui délimitent les informations
    /// \param[in,out] t_tabmots Une structure de matrice dynamique de mots
    FILE * fichiercsv;
    fichiercsv = fopen(filename, "r");
    int i = 0;
    char ligne_a_decouper[MAX] = "";
    while(fgets(ligne_a_decouper, MAXINT, fichiercsv) != NULL){
        int j = 0;
        char * token = strtok (ligne_a_decouper, delimiteur);
        while ( token != NULL ) {
            if(j == 2 && i > 0 && iord == OPT_I){
                char code[17];
                code_votant((*t_tabmots).tab[i][0], code);
                strcpy((*t_tabmots).tab[i][j], code);
            }else{
                strcpy((*t_tabmots).tab[i][j], token);
            }
            token = strtok (NULL, delimiteur);
            j++;
        }
        i++;
    }
    fclose(fichiercsv);
}