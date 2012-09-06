#include <stdlib.h>/*tres important!, pout aof() dans la fonction de change_format*/
#include <math.h>
#include<stdio.h>
#include<string.h>
#define PI 3.1415926
#ifndef MODULE_GLOBALE_H_INCLUDED
#define MODULE_GLOBALE_H_INCLUDED
// Définition de la structure de données
struct ville{
char nom_ville[100];
int pop; //variable stockant la population
float latitude; // on fera attention à changer le S par une multiplication par -1
float longitude;// le W par une multiplication par -1
};
typedef struct ville Ville;

float change_format(char* str);
//changer le format de ordonnee

float distance(Ville ville1, Ville ville2);
//calculer la distance entre 2 villes

Ville* tri_ville(Ville *ville, int flag, int nombre_de_ville);
//trier la liste des villes, en donnant flag=1 tri croissantment selon la population de la ville

Ville* x_premieres_villes(Ville *ville_triee, int x);
//choisir les X premieres villes 

void affiche_tableau(Ville* ville, int n);
//affiche le contenu de la laste_ville

#endif
