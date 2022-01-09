/* liste statique */
/* Vincent Dugat 2018 */

#ifndef listeSTAT
#define listeSTAT

#include "elementliste.h"

#define DIMMAX 100 /// \fn taille maximale de la liste statique
#define VIDE -1   /// \fn constante  pour indiquer que la liste est vide (par convention)

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

/// \struct pour créer des listes d'elements
struct liste {
    Elementliste Tabliste[DIMMAX];
    int Tete;
    int nbElt;
};

typedef struct liste liste;
int nbEltList(liste lst); /// \fn nombre d'éléments
/// \param[in] lst une liste
void createList(liste *p); /// \fn renvoie une liste statique
/// \param[in] p une liste
/// \param[in] e un element
void addFrontList(liste *p, Elementliste e); /// \fn ajoute un élément devant
/// \param[in] p une liste
/// \param[in] e un element
void addTailList(liste *p, Elementliste e); /// \fn ajoute un élément derrière
/// \param[in] p une liste
/// \param[in] e un element
void delTailList(liste *p); /// \fn supprime l'élément de fin
/// \param[in] p une liste
void delFrontList(liste *p); /// \fn supprime l'élément de tête
/// \param[in] p une liste
void headList(liste p, Elementliste *e); /// \fn renvoie l'élément de tête
/// \param[in] p une liste
/// \param[in] e un element
void tailList(liste p, Elementliste *e); /// \fn renvoie l'élément de fin
/// \param[in] p une liste
/// \param[in] e un element
bool emptyList(liste p); /// \fn renvoie true si la pile est vide, false sinon
/// \param[in] p une liste
bool fullList(liste p); /// \fn renvoie true si la pile est pleine, false sinon
/// \param[in] p une liste
void dumpList(liste p,FILE *fp); /// \fn affiche le contenu de la liste
/// \param[in] p une liste
/// \param[in] fp un fichier de sortie de la fonction
void swapEltList(Elementliste *a,Elementliste *b); // échange deux éléments de la liste
/// \param[in] a un element
/// \param[in] b un element
void bubbleSortList(liste *p); /// \fn trie la liste
/// \param[in] p une liste
void pickEltList(liste l,Elementliste *e,int index); /// \fn renvoie l'élément n° index
/// \param[in] l une liste
/// \param[in] e un element
/// \param[in] index un numero de position
bool belongEltList(liste p,Elementliste e); /// \fn true si l'élément est dans la liste
/// \param[in] p une liste
/// \param[in] e un element
#endif
