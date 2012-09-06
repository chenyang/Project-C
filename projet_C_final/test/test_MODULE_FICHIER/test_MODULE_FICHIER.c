#include "../../src/headers/MODULE_FICHIER.h"
#include "../../src/headers/MODULE_GLOBALE.h"
main()
{

FILE *fp_ville;
Ville *ville;
int nombre_de_ville=0;
FILE *fp_origine_html;
FILE *fp_test_html_1;
FILE *fp_test_html_2;
Ville *x_plus_grand_villes;


//----------partie fonctionnalite------


printf("\n\n==================================testing MODULE_FICHIER=============================================\n\n");

//-----------------------------------------------tester le change_format------------------------------------------------------------------------

printf("-----------------------------\ntester le change_format:\n");
printf("case1: 1.23N:\n");
printf("le resultat est %f:\n", change_format("1.23N"));//c'est bon
printf("case2: 2.23S:\n");
printf("le resultat est %f:\n", change_format("2.23S"));//c'est bon
printf("case3: 3.23P:\n");
printf("le resultat est %f:\n", change_format("3.23P"));//c'est faux, et ca donne 3.23, sauf si on les analyese avec ANTLR
printf("case4: 4.23:\n");
printf("le resultat est %f:\n", change_format("4.23"));//c'est faux, mais sauf si on les analyse avec ANTLR, trop complices..




//------------------------------------------------------------------tester la fonction read_ville et affiche_tableau--------------------------------------------------

printf("\n\n--------------tester read_ville, est-ce que les villes peuvent montre correctement?------------------\n");
printf("case1:");//on lit un fichier avec 1000 villes
printf("dans le repertoire ./villes.csv");
fp_ville=lire_fichier("./villes.csv");
ville=read_ville(fp_ville, &nombre_de_ville);
printf("\nil y a %d villes ds ce fichier et on affiche les premieres 10 villes\n", nombre_de_ville);
affiche_tableau(ville,10);//affichage de tableau pour le tester
nombre_de_ville=0;

printf("case2:");//on lit un fichier avec 2 lignes de donnes
printf("dans le repertoire ./test_ville1.csv");
fp_ville=lire_fichier("./test_ville1.csv");
ville=read_ville(fp_ville, &nombre_de_ville);
printf("\nil y a %d villes ds ce fichier et on affiche les premieres 10 villes\n", nombre_de_ville);
affiche_tableau(ville,10);//affichage de tableau pour le tester
nombre_de_ville=0;


//------------------------------------------------------------------tester la fonction ecrire_fichier--------------------------------------------------

printf("\n\n\n-------------tester plusieurs possibilite de ville sur google map, supposons que les fonctions ds MODULE_GLOBALE marche?:-------------------------\n");
fp_origine_html=lire_fichier("./map.html");
fp_test_html_1=fopen("./module_fichier_test_1.html", "w+");
fp_test_html_2=fopen("./module_fichier_test_2.html", "w+");
fp_ville=lire_fichier("./villes.csv");
ville=read_ville(fp_ville, &nombre_de_ville);
ville=tri_ville(ville, 1, nombre_de_ville);//tri croissantment

//case1: on affiche les 10 plus grandes villes sur google map
printf("\ncase1: on affiche les 10 plus grandes villes sur google map:\n");
x_plus_grand_villes=x_premieres_villes(ville, 10);
ecrire_fichier(x_plus_grand_villes, fp_origine_html, fp_test_html_1, 10);
printf("\n");

//case2: on affiche les 1000 plus grandes villes sur google map
printf("\ncase2: on affiche les 1000 plus grandes villes sur google map:\n");
ecrire_fichier(x_plus_grand_villes, fp_origine_html, fp_test_html_2, 1000);
printf("\n");




//-----------------------------------------------------------------tester la fonction lire fichier---------------------------------------------------

printf("\n\n-----------------------------\ntester lire_fichier, est-ce que le fichier existe?:\n");
printf("case1:\n");//on lit un fichier existe, on vois qu'est-ce qu'il montre
printf("dans le repertoire ./villes.csv");
fp_ville=lire_fichier("./villes.csv");
printf("\ncase2:\n");//on lit un fichier n'exite pas
printf("dans le repertoire ./XXX.csv");
fp_ville=lire_fichier("./XXX.csv");



}






