#include "../headers/MODULE_DIJKSTRA.h"


// création du tableau contenant la distance entre la ville de départ et l'ensemble des villes

float* creer_table_distance(Ville ville_depart, Ville *ville, int nombre_de_ville)
{
    int i;
    float *table_distance=malloc(sizeof(float)*nombre_de_ville);
    for(i=0; i<nombre_de_ville; i++)
    {
       // printf("%d, %s------ %s\n", i, ville_depart.nom_ville, ville[i].nom_ville);

        if( (ville[i].latitude == ville_depart.latitude) && (ville[i].longitude == ville_depart.longitude) )
            table_distance[i]=0.0;      // on intialise la ville de départ a 0
        else
            table_distance[i]=99999.0;      // on initialise toutes les autres villes a 99999
    }

    return table_distance;
}


// création du tableau indiquant les villes qui sont marquées ou non

int* creer_table_marque(int nombre_de_ville)
{
    int i;
    int *table_marque=malloc(sizeof(int)*nombre_de_ville);
    for(i=0; i<nombre_de_ville; i++)
    {
            table_marque[i]=1;      // on initialise le tableau a 1 ( ville non marquée)
    }

    return table_marque;

}


// création du tableau indiquant le numéro de la ville précédente de celle dont le numéro est l'indice i

int* creer_table_pere(int nombre_de_ville)
{
     int i;
     int *table_pere=(int *)malloc(sizeof(int)*nombre_de_ville);
     for(i=0; i<nombre_de_ville; i++)
     {
      table_pere[i]=-1;          // on initialise le tableau a -1 (pas de père au début)
     }

    return table_pere;

}


//est-ce que tous les villes sont extraites??

int toutes_villes_extraites(int *table_marque, int nombre_de_ville)
{
    int i=0;

    while(i<nombre_de_ville+1 && table_marque[i]!=-2)
    {
        i++;
    }

    //on suppose que tous les villes sont visitees
    // si on trouve une ville qui est marquée avant la fin du fichier on renvoit faux

    if(i== nombre_de_ville) return 1;
    else return 0;

}


// fonction qui calcule quel est la ville dont la distance au départ est minimum

int extraire_min(float *table_distance, int *table_marque,  int nombre_de_ville)
{
    int i, j, min;
    int num_ville_min=0;
    min=99999;  // etape suivante a l'initialisation


    for(i=0; i<nombre_de_ville; i++)
    {

        if(table_marque[i] != -2)       // si la ville est non visitée
        {
            if(table_distance[i]<=min)  // si il y a une distance plus petite
            {
                min=table_distance[i];  //on remplace le min
                 num_ville_min=i;      // on enregistre le numéro de la ville la plus proche
            }
        }
    }

    return num_ville_min;    // on renvoit le numéro de la ville minimum
}


// modification de la table marque ( on marque la ville visitée)
int* extraire_update_table_marque(float *table_distance, int *table_marque, int nombre_de_ville)
{
    int i, j, min;
    int num_ville_min=0;
    min=99999;

    for(i=0; i<nombre_de_ville; i++)
    {
        if(table_marque[i] != -2)       // si la ville est non visitée
        {
            if(table_distance[i]<=min)  // si il y a une distance plus petite
            {
                min=table_distance[i];  //on remplace le min
                 num_ville_min=i;      // on enregistre le numéro de la ville la plus proche
            }
        }
    }

    table_marque[num_ville_min]=-2; // on modifit le tableau ( on marque la ville dont la distance est la plus proche du départ)
    return table_marque;    // on renvoit le pointeur sur le tableau modifié
}


// on applique la fonction relacher vu en graphe;
float* relacher_table_distance(float *table_distance, int X, int Y, Ville *ville)   //X est numéro de la ville qu'on observe et Y sont ses successeurs
{

    //si il existe une distance dans la table des successeurs qui soit supérieure a celle de la ville précédente + la distance entre X et ses successure en question

    if(table_distance[Y]>table_distance[X]+distance(ville[X], ville[Y]))
        {
            table_distance[Y]=table_distance[X]+distance(ville[X], ville[Y]);   // on modifit la table distance
        }
        return table_distance;
}

// on applique la fonction relacher vu en graphe qui indique qui est le père de la ville Y
int* relacher_table_pere(float *table_distance, int *table_pere, int X, int Y, Ville *ville)    //X est numéro de la ville qu'on observe et Y sont ses successeurs
{
    //si il existe une distance dans la table des successeurs qui soit supérieure a celle de la ville précédente + la distance entre X et ses successure en question

    if(table_distance[Y]>table_distance[X]+distance(ville[X], ville[Y]))
        {
           table_pere[Y]=X;     // on modifit le tableau des pères en indiquant que X est le père de Y
        }
    return table_pere;
}



//a l'interieur de erire_fichier_chemin
int cherche_chemin_1(Ville *ville, FILE *fp_new_html, int *table_pere, int No_de_depart, int No_de_dest, int i)//pour poursuivre le trace
{
    int No_de_pere=table_pere[No_de_dest];
    fprintf(fp_new_html, "[%d, %.2f, %.2f], \n", i, ville[No_de_pere].latitude, ville[No_de_pere].longitude);
    i++;
    while(No_de_pere!=No_de_depart)
    {
        No_de_pere=cherche_chemin_1(ville, fp_new_html, table_pere, No_de_depart, No_de_pere, i);
    }

    return No_de_pere;
}

//a l'interieur de erire_fichier_chemin
int cherche_chemin_2(FILE *fp_new_html, int *table_pere, int No_de_depart, int No_de_dest, int i)//pour poursuivre le trace
{
    int No_de_pere=table_pere[No_de_dest];
    fprintf(fp_new_html, "[%d, %d], \n", i, i+1);
    i++;
    while(No_de_pere!=No_de_depart)
    {
        No_de_pere=cherche_chemin_2(fp_new_html, table_pere, No_de_depart, No_de_pere, i);
    }

    return No_de_pere;
}


void ecrire_fichier_chemin(Ville *ville, FILE *fp_origine_html, FILE *fp_new_html_2, int *table_pere, int No_de_depart, int No_de_dest)
{
    char ligne[100];//characteres de chaque ligne dans html
//manipulation de html, loading map.html-->map_out.html, premiere 14 lignes
    int i;
    for(i=0; i<14; i++)
    {
        fgets(ligne, 100, fp_origine_html);
        fputs(ligne, fp_new_html_2);
    }


//on attaque sur .html

    fprintf(fp_new_html_2, "var coordinates = [\n");
    fprintf(fp_new_html_2, "[%d, %.2f, %.2f], \n", 1, ville[No_de_dest].latitude, ville[No_de_dest].longitude);
    cherche_chemin_1(ville, fp_new_html_2, table_pere, No_de_depart, No_de_dest, 2);//pour poursuivre le trace
    fprintf(fp_new_html_2, "];\n");

    fprintf(fp_new_html_2, " var edges = [\n");
    cherche_chemin_2(fp_new_html_2, table_pere, No_de_depart, No_de_dest, 1);

    fprintf(fp_new_html_2, "];\n");
    fprintf(fp_new_html_2, "map_center = [46.468133, 2.351074]\n\n");

    for(i=15; i<=29; i++)
    {
        fgets(ligne, 100, fp_origine_html);// do nothing
    }

    for(i=30; i<=86; i++)
    {
        fgets(ligne,100, fp_origine_html);
        fputs(ligne, fp_new_html_2);
    }

    rewind(fp_origine_html);
    fclose(fp_new_html_2);

}




