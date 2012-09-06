#include"MODULE_GLOBALE.h"
#ifndef MODULE_FICHIER_H_INCLUDED
#define MODULE_FICHIER_H_INCLUDED



FILE* lire_fichier(char* path_fichier);
//get fichier_pointeur

Ville* read_ville(FILE* fp, int* nombre_de_ville);
//get pointeur Ville apres avoir lit le fichier

void ecrire_fichier(Ville *ville, FILE *fp_origine_html, FILE *fp_new_html, int x);
//ecrire les X plus grandes villes sur Google Map

#endif
