#include "../../src/headers/MODULE_APPENDICE.h"
#include "../../src/headers/MODULE_FICHIER.h"

main()
{
    Ville depart;
    Ville dest;
    printf("=====================================testing MODULE_APPENDICE=====================================");
    printf("On suppose que le fichier de ville existe et marche bien:\n");


//Cas 1
    printf("---------Cas1----------\n");//ds cas 1, on ecrire normalement
    depart=choisir_ville_depart("./villes.csv");
    printf("ville depart est :%s\n", depart.nom_ville);
    dest=choisir_ville_dest("./villes.csv");
    printf("ville dest est :%s\n", dest.nom_ville);



//Cas 2
    printf("---------Cas2------avec chiffre ou pas majuscule----\n");//ds cas 2, on ecrire des chiffre, ou pas majuscule pour le premier mot
    depart=choisir_ville_depart("./villes.csv");
    printf("ville depart est :%s\n", depart.nom_ville);
    dest=choisir_ville_dest("./villes.csv");
    printf("ville dest est :%s\n", dest.nom_ville);



    //la limite de ce programme est de on ne peut pas restraint ce que l'utilisateur a saisi.,.


}
