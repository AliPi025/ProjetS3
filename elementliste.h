/* liste statique */
/* Vincent Dugat 2018 */

/* Pour éviter les inclusions multiples */

#ifndef ELEMENTLISTE_H
#define ELEMENTLISTE_H

#include "global.h" // définit le type t_arc_p

typedef t_arc_p Elementliste;
void saisie_element(Elementliste *e, int origine, int destination, int poids); /// \fn saisie d'un element
/// \param[in] e un element
/*void saisie_element(Elementliste *e); /// \fn saisie d'un element
/// \param[in] e un element*/
void copie_element(Elementliste *cible, Elementliste source); /// \fn copie d'un element
/// \param[in] cible un element à modifier
/// \param[in] source un element copié
void afficher_element(Elementliste e,FILE *fp); /// \fn affichage d'un element
/// \param[in] e un element
/// \param[in] fp un fichier de sortie de la fonction
bool cmp_elements(Elementliste e1,Elementliste e2); /// \fn comparaison de deux elements
/// \param[in] e1 un element
/// \param[in] e2 un element

#endif
