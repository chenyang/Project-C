#include"../../src/headers/MODULE_GLOBALE.h"
#include"../../src/headers/MODULE_ARBRE.h"

main()
{
     //------------------initiation des attributs------------------------
    int i;
    int nombre_de_ville=0;//le nombre de ville du fichier
    int limite=0;
    int No_de_ville_X;//Ville_X
    int No_de_ville_Y;//succeseur de X
    float *table_prim_distance;
    int *table_prim_marque;
    int *table_prim_pere;
    int No_de_depart=0;
    int No_de_dest=0;
    Ville *ville;
    int N;//le numero demonstre les N plus grandes villes pour afficher aerien couvrant
    Ville *x_plus_grand_villes;//les x plus grands ville
    int trouvee;
    FILE *fp_ville;
    FILE *fp_origine_html;
    FILE *fp_test_html_1;
    FILE *fp_test_html_2;

    printf("\n\n==================================testing MODULE_ARBRE_COUVRANT=============================================\n\n");

    fp_ville=lire_fichier("./villes.csv");
    ville=read_ville(fp_ville, &nombre_de_ville);
    fp_test_html_1=fopen("./module_arbre_test_1.html", "w+");
    fp_test_html_2=fopen("./module_arbre_test_2.html", "w+");
    fp_origine_html=lire_fichier("./map.html");



//---------------------------------Case 1 les 15 plus grandes villes a faire dans l'arbre couvrant----------------------------------
    printf("------------Case 1 les 15 plus grandes villes a faire dans l'arbre couvrant---------");
    N=15;//premiere 15 plus grandes villes
    ville=tri_ville(ville, 1, nombre_de_ville);
    x_plus_grand_villes=x_premieres_villes(ville, N);
    //affiche_tableau(x_plus_grand_villes, N);

    table_prim_distance=creer_table_prim_distance(x_plus_grand_villes, N);
    table_prim_marque=creer_table_prim_marque(N);
    table_prim_pere=creer_table_prim_pere(N);
    table_prim_pere[0]=0;//!!!

while(!tous_villes_extraire_prim(table_prim_marque, N))
{
    No_de_ville_X=extraire_prim_min(table_prim_distance, table_prim_marque, N);
     //printf("ville_X c'est :%s et la distance :%f\n", x_plus_grand_villes[No_de_ville_X].nom_ville, table_prim_distance[No_de_ville_X]);
     table_prim_marque=extraire_update_table_prim_marque(table_prim_distance, table_prim_marque, N);
    for(No_de_ville_Y=0; No_de_ville_Y<N; No_de_ville_Y++)//pour chaque voisin de ville_X. cette fois par rapport au DIJKSTRA, on n'a pas de condition stricte..
    {
        table_prim_pere=relacher_table_prim_pere(table_prim_distance, table_prim_marque, table_prim_pere, No_de_ville_X, No_de_ville_Y, x_plus_grand_villes);
        table_prim_distance=relacher_table_prim_distance(table_prim_distance, table_prim_marque, No_de_ville_X, No_de_ville_Y, x_plus_grand_villes);
    }

}

    ecrire_fichier_couvrant_minimal(fp_origine_html, fp_test_html_1, table_prim_pere, N, x_plus_grand_villes);
    printf("\n\necrire fichier fichier_couvrant_minimal done =)\n\n");





//---------------------------------Case 2 les 1000 plus grandes villes a faire dans l'arbre couvrant----------------------------------
    printf("-----------Case 2 les 1000 plus grandes villes a faire dans l'arbre couvrant-----------------");
    N=1000;//premiere 15 plus grandes villes
    ville=tri_ville(ville, 1, nombre_de_ville);
    x_plus_grand_villes=x_premieres_villes(ville, N);
    //affiche_tableau(x_plus_grand_villes, N);

    table_prim_distance=creer_table_prim_distance(x_plus_grand_villes, N);
    table_prim_marque=creer_table_prim_marque(N);
    table_prim_pere=creer_table_prim_pere(N);
    table_prim_pere[0]=0;//!!!

while(!tous_villes_extraire_prim(table_prim_marque, N))
{
    No_de_ville_X=extraire_prim_min(table_prim_distance, table_prim_marque, N);
     //printf("ville_X c'est :%s et la distance :%f\n", x_plus_grand_villes[No_de_ville_X].nom_ville, table_prim_distance[No_de_ville_X]);
     table_prim_marque=extraire_update_table_prim_marque(table_prim_distance, table_prim_marque, N);
    for(No_de_ville_Y=0; No_de_ville_Y<N; No_de_ville_Y++)//pour chaque voisin de ville_X. cette fois par rapport au DIJKSTRA, on n'a pas de condition stricte..
    {
        table_prim_pere=relacher_table_prim_pere(table_prim_distance, table_prim_marque, table_prim_pere, No_de_ville_X, No_de_ville_Y, x_plus_grand_villes);
        table_prim_distance=relacher_table_prim_distance(table_prim_distance, table_prim_marque, No_de_ville_X, No_de_ville_Y, x_plus_grand_villes);
    }

}

    ecrire_fichier_couvrant_minimal(fp_origine_html, fp_test_html_2, table_prim_pere, N, x_plus_grand_villes);
    printf("\n\necrire fichier fichier_couvrant_minimal done =)\n\n");




}
