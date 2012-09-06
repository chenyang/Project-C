#include"MODULE_FICHIER.h"
#ifndef MODULE_DIJKSTRA_H_INCLUDED
#define MODULE_DIJKSTRA_H_INCLUDED


float* creer_table_distance(Ville ville_depart, Ville *ville, int nombre_de_ville);
//creer la table_distance pour calculer DIJKSTRA

int* creer_table_marque(int nombre_de_ville);
//creer la table_marque pour DIJKSTRA

int* creer_table_pere(int nombre_de_ville);
//creer la table_pere pour DIJKSTRA

int extraire_min(float *table_distance, int *table_marque, int nombre_de_ville);
//retourner le numero de ville extraire..

int* extraire_update_table_marque(float *table_distance, int *table_marque, int nombre_de_ville);
//update la table_marque apres extrire_min

float *relacher_table_distance(float *table_distance, int x, int y, Ville *ville);
//la fonction relacher, en relachant table_distance

int* relacher_table_pere(float *table_distance, int *table_pere, int X, int Y, Ville *ville);
//la fonction relacher, en relachant table_distance

int toutes_villes_extraites(int *table_marque, int nombre_de_ville);
//verifier est-ce que toutes les villes sont extraites

int cherche_chemin_1(Ville *ville, FILE *fp_new_html, int *table_pere, int No_de_depart, int No_de_dest, int i);
//inner fonction dans ecrire_fichier_chemin
int cherche_chemin_2(FILE *fp_new_html, int *table_pere, int No_de_depart, int No_de_dest, int i);
//inner fonction dans ecrire_fichier_chemin
void ecrire_fichier_chemin(Ville *ville, FILE *fp_origine_html, FILE *fp_new_html_2, int *table_pere, int No_de_depart, int No_de_dest);
//ecrire le DIJKSTRA sur le Google Map




#endif
