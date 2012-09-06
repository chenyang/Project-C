#include"../../src/headers/MODULE_GLOBALE.h"
#include"../../src/headers/MODULE_DIJKSTRA.h"

main()
{
    //------------------initiation des attributs------------------------
    int i;
    int nombre_de_ville=0;//le nombre de ville du fichier
    int limite=0;
    int No_de_ville_X;//Ville_X
    int No_de_ville_Y;//succeseur de X
    float *table_distance;
    int *table_marque;
    int *table_pere;
    int No_de_depart=0;
    int No_de_dest=0;
    Ville *ville;
    Ville depart;
    Ville dest;
    int N;//le numero demonstre les N plus grandes villes pour afficher aerien couvrant
    Ville *x_plus_grand_villes;//les x plus grands ville
    int trouvee;
    FILE *fp_ville;
    FILE *fp_origine_html;
    FILE *fp_test_html_1;
    FILE *fp_test_html_2;
    FILE *fp_test_html_3;

    printf("\n\n==================================testing MODULE_DIJKSTRA=============================================\n\n");

    fp_ville=lire_fichier("./villes.csv");
    ville=read_ville(fp_ville, &nombre_de_ville);
    fp_test_html_1=fopen("./module_dijkstra_test_1.html", "w+");
    fp_test_html_2=fopen("./module_dijkstra_test_2.html", "w+");
    fp_test_html_3=fopen("./module_dijkstra_test_3.html", "w+");
    fp_origine_html=lire_fichier("./map.html");


//-----------------------case 1: de Strasbourg a Tours avec la limite 150km----------------------------------

printf("-------------------------------------cas1: de Strasbourg a Tours avec la limite 150km-------------------------\n");
depart=ville[879];//depart est Strasbourg
dest=ville[907];//dest est Tours
limite=150;//la limite d'avion est de 150km

//pour creer les tables necessaire pour realiser le Dijkstra
table_distance=creer_table_distance(depart, ville, nombre_de_ville);
table_marque=creer_table_marque(nombre_de_ville);
table_pere=creer_table_pere(nombre_de_ville);
//----------------------------------------Dijkstra----------------------------------------------------------
trouvee=0;
while(!toutes_villes_extraites(table_marque, nombre_de_ville)&&!trouvee)//===>tant que il y a des villes non extraire..
{
    No_de_ville_X=extraire_min(table_distance, table_marque, nombre_de_ville);
    //printf("ville_X c'est :%s et la distance :%f\n", ville[No_de_ville_X].nom_ville, table_distance[No_de_ville_X]);
    if(ville[No_de_ville_X].latitude==dest.latitude&&ville[No_de_ville_X].longitude==dest.longitude)
    {trouvee=1;}//si on trouve la ville destiaire.
    else{
        table_marque=extraire_update_table_marque(table_distance, table_marque, nombre_de_ville);
        for(No_de_ville_Y=0; No_de_ville_Y<nombre_de_ville; No_de_ville_Y++)
        {
            if(distance(ville[No_de_ville_X], ville[No_de_ville_Y])<=limite)//pour les succeseurs de ville_X
            {
                //Attention!! ici l'ordre de fonction est un peu different d'algorithm in paper: la raison:par definition de notre fonction
                //si relache table_distance tout a bord, la fonction relacher_table_pere ne marche bien!!
                //premierement, je note les peres; Ensuit, je fait relacher_table_distance//
                table_pere=relacher_table_pere(table_distance, table_pere, No_de_ville_X, No_de_ville_Y, ville);
                table_distance=relacher_table_distance(table_distance, No_de_ville_X, No_de_ville_Y, ville);
            }
        }
    }
}

for(i=0; i<nombre_de_ville; i++){
    if(ville[i].latitude==depart.latitude&&ville[i].longitude==depart.longitude)
        No_de_depart=i;
    if(ville[i].latitude==dest.latitude&&ville[i].longitude==dest.longitude)
        No_de_dest=i;
}


printf("apres Dijkstra, la distance entre ces 2 villes est: %f\n", table_distance[No_de_dest]);

if(table_distance[No_de_dest]!=99999.0)
    {
        ecrire_fichier_chemin(ville, fp_origine_html, fp_test_html_1, table_pere, No_de_depart, No_de_dest);
        printf("ecrire map_chemin_done =) \n\n");
    }
    else
    {
        printf("on ne peut pas arriver :( \n\n");
    }



//-----------------------case 2: de Strasbourg a Tours avec la limite 10km----------------------------------
printf("\n-------------------------------------cas2: de Strasbourg a Tours avec la limite 10km-------------------------\n");
depart=ville[879];//depart est Strasbourg
dest=ville[907];//dest est Tours
limite=10;//la limite d'avion est de 10km

//pour creer les tables necessaire pour realiser le Dijkstra
table_distance=creer_table_distance(depart, ville, nombre_de_ville);
table_marque=creer_table_marque(nombre_de_ville);
table_pere=creer_table_pere(nombre_de_ville);
//----------------------------------------Dijkstra----------------------------------------------------------
trouvee=0;
while(!toutes_villes_extraites(table_marque, nombre_de_ville)&&!trouvee)//===>tant que il y a des villes non extraire..
{
    No_de_ville_X=extraire_min(table_distance, table_marque, nombre_de_ville);
    //printf("ville_X c'est :%s et la distance :%f\n", ville[No_de_ville_X].nom_ville, table_distance[No_de_ville_X]);
    if(ville[No_de_ville_X].latitude==dest.latitude&&ville[No_de_ville_X].longitude==dest.longitude)
    {trouvee=1;}//si on trouve la ville destiaire.
    else{
        table_marque=extraire_update_table_marque(table_distance, table_marque, nombre_de_ville);
        for(No_de_ville_Y=0; No_de_ville_Y<nombre_de_ville; No_de_ville_Y++)
        {
            if(distance(ville[No_de_ville_X], ville[No_de_ville_Y])<=limite)//pour les succeseurs de ville_X
            {
                //Attention!! ici l'ordre de fonction est un peu different d'algorithm in paper: la raison:par definition de notre fonction
                //si relache table_distance tout a bord, la fonction relacher_table_pere ne marche bien!!
                //premierement, je note les peres; Ensuit, je fait relacher_table_distance//
                table_pere=relacher_table_pere(table_distance, table_pere, No_de_ville_X, No_de_ville_Y, ville);
                table_distance=relacher_table_distance(table_distance, No_de_ville_X, No_de_ville_Y, ville);
            }
        }
    }
}

for(i=0; i<nombre_de_ville; i++){
    if(ville[i].latitude==depart.latitude&&ville[i].longitude==depart.longitude)
        No_de_depart=i;
    if(ville[i].latitude==dest.latitude&&ville[i].longitude==dest.longitude)
        No_de_dest=i;
}


printf("apres Dijkstra, la distance entre ces 2 villes est: %f\n", table_distance[No_de_dest]);

if(table_distance[No_de_dest]!=99999.0)
    {
        ecrire_fichier_chemin(ville, fp_origine_html, fp_test_html_2, table_pere, No_de_depart, No_de_dest);
        printf("ecrire map_chemin_done =) \n\n");
    }
    else
    {
        printf("on ne peut pas arriver :( \n\n");
    }






//-----------------------case 3: de Strasbourg a Tours avec la limite 999999999km----------------------------------
printf("\n------------------------cas3: de Strasbourg a Tours avec la limite 9999999999km---------------------\n");
depart=ville[879];//depart est Strasbourg
dest=ville[907];//dest est Tours
limite=999999999;//la limite d'avion est de 10km

//pour creer les tables necessaire pour realiser le Dijkstra
table_distance=creer_table_distance(depart, ville, nombre_de_ville);
table_marque=creer_table_marque(nombre_de_ville);
table_pere=creer_table_pere(nombre_de_ville);
//----------------------------------------Dijkstra----------------------------------------------------------
trouvee=0;
while(!toutes_villes_extraites(table_marque, nombre_de_ville)&&!trouvee)//===>tant que il y a des villes non extraire..
{
    No_de_ville_X=extraire_min(table_distance, table_marque, nombre_de_ville);
    //printf("ville_X c'est :%s et la distance :%f\n", ville[No_de_ville_X].nom_ville, table_distance[No_de_ville_X]);
    if(ville[No_de_ville_X].latitude==dest.latitude&&ville[No_de_ville_X].longitude==dest.longitude)
    {trouvee=1;}//si on trouve la ville destiaire.
    else{
        table_marque=extraire_update_table_marque(table_distance, table_marque, nombre_de_ville);
        for(No_de_ville_Y=0; No_de_ville_Y<nombre_de_ville; No_de_ville_Y++)
        {
            if(distance(ville[No_de_ville_X], ville[No_de_ville_Y])<=limite)//pour les succeseurs de ville_X
            {
                //Attention!! ici l'ordre de fonction est un peu different d'algorithm in paper: la raison:par definition de notre fonction
                //si relache table_distance tout a bord, la fonction relacher_table_pere ne marche bien!!
                //premierement, je note les peres; Ensuit, je fait relacher_table_distance//
                table_pere=relacher_table_pere(table_distance, table_pere, No_de_ville_X, No_de_ville_Y, ville);
                table_distance=relacher_table_distance(table_distance, No_de_ville_X, No_de_ville_Y, ville);
            }
        }
    }
}

for(i=0; i<nombre_de_ville; i++){
    if(ville[i].latitude==depart.latitude&&ville[i].longitude==depart.longitude)
        No_de_depart=i;
    if(ville[i].latitude==dest.latitude&&ville[i].longitude==dest.longitude)
        No_de_dest=i;
}


printf("apres Dijkstra, la distance entre ces 2 villes est: %f\n", table_distance[No_de_dest]);

if(table_distance[No_de_dest]!=99999.0)
    {
        ecrire_fichier_chemin(ville, fp_origine_html, fp_test_html_3, table_pere, No_de_depart, No_de_dest);
        printf("ecrire map_chemin_done =) \n\n");
    }
    else
    {
        printf("on ne peut pas arriver :( \n\n");
    }






}


