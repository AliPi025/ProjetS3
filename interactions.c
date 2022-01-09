/// \brief Fonctions s'occupants de l'interaction avec l'utilisateur
/// \file interactions.c
/// \author Pierre ALIBERT
/// \date Décembre 2021
#include "global.h"

/// \fn Affiche un message d'erreur
void erreur(char *message){
    /// \param[in] message Une phrase expliquant l'erreur  
    fprintf(stderr, "%s", message);
    exit(ERR);
}

/// \fn Affiche une aide sur l'utilisation du système de vote
void help(){
    printf("NOM\n\tvote - renvoie un résultat de vote selon les différentes options\n\n");
    printf("SYNOPSIS\n\tvote OPTION[...] FICHIER.csv\n\n");
    printf("DESCRIPTION\n\tAffiche les différents calculs afin d'aboutir au résultat de vote spécifié.\n\n");
    printf("-i, le fichier csv est le résultat d'un vote par classement(ensemble de ballots).\n\n");
    printf("-d, le fichier csv est une matrice de duels (désactive l'emploi des arguments uni1 et uni2 de l'option -m).\n\n");
    printf("-o [<nom>.txt], écrit les calculs effectués sur le fichier <nom>.txt ou sur stdout s'il n'y pas de nom.\n\n");
    printf("-m <nom_de_methode>, applique une methode de scrutin parmi {uni1, uni2, cm, cs, all}\n\n");
}

/// \fn Vérifie les options liées aux balises
int verifop(int i, int indice, int notbis, char * tab_balises[], char * balise, char * extension, int argc, char * argv[]){
    /// \param[in] i Position de l'argument à vérifier
    /// \param[in] indice Position à laquelle écrire l'argument s'il est juste
    /// \param[in] notbis Entier permettant de vérifier qu'une balise n'apparaît pas plusieurs fois en entrée
    /// \param[in,out] tab_balises Tableau où sont triés les balises et arguments
    /// \param[in] balise Nom de la balise traitée
    /// \param[in] extension Nom de l'extension dont il faut vérifier la présence
    /// \param[in] argc Dimension de argv
    /// \param[in] argv Tableau de caractères contenant les entrées utilisateur
    /// \return Si l'argument concorde ou non avec la balise
    if(i+1<argc && strlen(argv[i+1]) > strlen(extension) && notbis == OPT_H){
        char *ext = strrchr(argv[i+1], '.');
        if(!ext || ext == argv[i+1]) 
            ext = "";
        if(!strcmp(ext, extension) || (!strcmp(balise, "-m") && (!strcmp(argv[i+1], "uni1") || !strcmp(argv[i+1], "uni2") || !strcmp(argv[i+1], "cm") || !strcmp(argv[i+1], "cs") || !strcmp(argv[i+1], "all")))){
            tab_balises[indice] = argv[i];
            tab_balises[indice+1] = argv[i+1];
        }else
            return ERR;
    }else
        return ERR;
    return SUCCESS;
}

/// \fn Récupère les paramètres en entrée
int getop(char *tab_balises[], int argc, char *argv[]){
    /// \param[in,out] tab_balises Tableau où sont triés les balises et arguments
    /// \param[in] argc un nombre de paramètres sur la ligne d'entrée 
    /// \param[in] argv un tableau des paramètres de la ligne d'entrée
    /// \return Si l'entrée utilisateur est correcte ou non
    int iord = OPT_H, m = OPT_H, o = OPT_H;
    if(argc == 1){
        erreur("Erreur : Balises manquantes\n");
        return ERR;
    }else if(argc > NB_BALISES+NBMAXOPTIONS+1){
        erreur("Erreur : Trop de balises\n");
        return ERR;
    }else if(!strcmp(argv[1], "help")){
        help();
        exit(SUCCESS);
    }
    int test;
    for(int i = 1; i<argc; i += 2){
        if(!strcmp(argv[i], "-i") || !strcmp(argv[i], "-d")){
            test = verifop(i, 0, iord, tab_balises, argv[i], ".csv", argc, argv);
            iord = (!strcmp(argv[i], "-i")) ? OPT_I : OPT_D;
        }else if(!strcmp(argv[i], "-o")){
            test = verifop(i, 2, o, tab_balises, argv[i], ".txt", argc, argv);
            o = OPT_O;
        }else if(!strcmp(argv[i],"-m")){
            test = verifop(i, 4, m, tab_balises, argv[i], "", argc, argv);
            m = OPT_M;
        }else{
            erreur("Erreur : Balise inconnue\n");
            return ERR;
        }
        if(test == ERR){
            erreur("Erreur : Argument incorrect\n");
            return ERR;
        }
    }
    if(iord == OPT_H){
        erreur("Erreur : Balise -i | -d absente\n");
        return ERR;
    }else if(iord == OPT_D && (!strcmp(tab_balises[5], "uni1") || !strcmp(tab_balises[5], "uni2")))
            erreur("Erreur : Methode incompatible avec le type du fichier\n");
    return SUCCESS;
}

/// \fn Affiche les résulats de vote
void affiche_resultat(FILE *outfp,char * scrutin,int nbCand, int nbVotants ,float score,char * vainqueur){
    /// \param[in] outfp Un fichier de sortie ou stdout
    /// \param[in] scrutin Nom de méthode de scrutin
    /// \param[in] nbCand Nombre de candidats
    /// \param[in] nbVotants Nombre de votants
    /// \param[in] score Nombre réel du score du vainqueur
    /// \param[in] vainqueur Nom du vainqueur à l'élection
    if(score >= 0)
        fprintf(outfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.1lf%%\n", scrutin, nbCand, nbVotants, vainqueur, score);
    else
        fprintf(outfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", scrutin, nbCand, nbVotants, vainqueur);
}