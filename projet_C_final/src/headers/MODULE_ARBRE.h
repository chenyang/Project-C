#include"MODULE_FICHIER.h"
#ifndef MODULE_ARBRE_H_INCLUDED
#define MODULE_ARBRE_H_INCLUDED

//----------Algorithm_Prim--------------------
float* creer_table_prim_distance(Ville *ville, int nombre_de_ville);
//creer la table_prim_distance pour calculer Prim

int* creer_table_prim_marque(int nombre_de_ville);
//creer la table_prim_marque pour Prim

int* creer_table_prim_pere(int nombre_de_ville);
//creer la table_prim_pere pour Prim

int extraire_prim_min(float *table_prim_distance, int *table_prim_marque, int nombre_de_ville);
//retourner le numero de ville extraire..

int* extraire_update_table_prim_marque(float *table_prim_distance, int *table_prim_marque, int nombre_de_ville);
//update la table_prim_marque apres extrire_min

int tous_villes_extraire_prim(int *table_prim_marque, int nombre_de_ville);
//verifier est-ce que toutes les villes sont extraites

float* relacher_table_prim_distance(float *table_prim_distance, int *table_prim_marque, int X, int Y, Ville *ville);
//la fonction relacher, en relachant table_prim_distance

int* relacher_table_prim_pere(float *table_prim_distance, int *table_prim_marque, int *table_prim_pere, int X, int Y, Ville *ville);
//la fonction relacher, en relachant table_prim_distance

void ecrire_fichier_couvrant_minimal(FILE *fp_origine_html, FILE *fp_new_html_3, int *table_prim_pere, int N, Ville *x_plus_grand_villes);
//ecrire l'arbre minimale couvrant sur le Google Map


#endif
