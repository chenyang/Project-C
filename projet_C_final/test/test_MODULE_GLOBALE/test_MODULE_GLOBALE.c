#include "../../src/headers/MODULE_GLOBALE.h"
#include "../../src/headers/MODULE_FICHIER.h"
main()
{
    FILE *fp_ville;
    Ville *ville;

    //on teste ici seulement la fonction affiche_tableau, tri_ville et x_premieres_villes 
    printf("\n\n==================================testing MODULE_GLOBALE=============================================\n\n");
    printf("on trier les villes, en supposant que le fichier fonctionne bien\n ");

    int nombre_de_ville=0;
    fp_ville=lire_fichier("./villes.csv");
    ville=read_ville(fp_ville,&nombre_de_ville);
    printf("\n\n--------on vas afficher les 50 premieres villes, en utilisant affiche_tableau-------\n");
    affiche_tableau(ville, 50);//on affiche les 50 premieres villes apres tri decrossant
    printf("\n\n------on vas ensuite affichier les 20 premieres villes apres triee, en utilisant x_premieres_villes-----\n\n");
    ville=tri_ville(ville, 1, nombre_de_ville);
    ville=x_premieres_villes(ville, 20);
    affiche_tableau(ville, 20);//afficher les 20 premires villes apres triee

}
