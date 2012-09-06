#include "../headers/MODULE_ARBRE.h"


//------------------------------------Prim---------------------------------------------------------------------


// création du tableau contenant la distance entre la ville de départ et l'ensemble des villes

float* creer_table_prim_distance(Ville *ville, int nombre_de_ville)
{
    int i;
    float *table_prim_distance=malloc(sizeof(float)*nombre_de_ville);
    table_prim_distance[0]=0.0;     //en fait, on parcours de plus grand ville
    for(i=1; i<nombre_de_ville; i++)
    {
            table_prim_distance[i]=99999.0; // on initialise toutes les autres villes a 99999
    }

    return table_prim_distance;
}


// création du tableau indiquant les villes qui sont marquées ou non

int* creer_table_prim_marque(int nombre_de_ville)
{
    int i;
    int *table_prim_marque=malloc(sizeof(int)*nombre_de_ville);
    for(i=0; i<nombre_de_ville; i++)
    {
            table_prim_marque[i]=1; // on initialise le tableau a 1 ( ville non marquée)
    }


    return table_prim_marque;

}


// création du tableau indiquant le numéro de la ville précédente de celle dont le numéro est l'indice i

int* creer_table_prim_pere(int nombre_de_ville)
{
     int i;
     int *table_prim_pere=(int *)malloc(sizeof(int)*nombre_de_ville);
     for(i=0; i<nombre_de_ville; i++)
     {
      table_prim_pere[i]=-1;         // on initialise le tableau a -1 (pas de père au début)
     }

    return table_prim_pere;

}


//est-ce que tous les villes sont extraites??

int extraire_prim_min(float *table_prim_distance, int *table_prim_marque, int nombre_de_ville)
{
    int i;
    int flag=0;
    float min=9999.0;


 for(i=0; i<nombre_de_ville; i++)
    {

        if(table_prim_marque[i] != -2)       // si la ville est non visitée
        {
            if(table_prim_distance[i]<=min)  // si il y a une distance plus petite
            {
                min=table_prim_distance[i]; //on remplace le min
                flag=i;                     // on enregistre le numéro de la ville la plus proche
            }
        }
    }
    return flag;
}


// modification de la table marque ( on marque la ville visitée)
int* extraire_update_table_prim_marque(float *table_prim_distance, int *table_prim_marque, int nombre_de_ville)
{
    int i;
    int flag=0;
    float min=99999.0;

    for(i=0; i<nombre_de_ville; i++)
    {
      if(table_prim_marque[i] != -2)       // si la ville est non visitée
        {
            if(table_prim_distance[i]<=min) // si il y a une distance plus petite
            {
                min=table_prim_distance[i]; //on remplace le min
                flag=i;                     // on enregistre le numéro de la ville la plus proche
            }
        }
    }

    table_prim_marque[flag]=-2;
    return table_prim_marque;
}


//est-ce que tous les villes sont extraites??
int tous_villes_extraire_prim(int *table_prim_marque, int nombre_de_ville)//est-ce que tous les villes sont extraire??
{
    int result=1;//on suppose que tous les villes sont visitees
    int i;

    for(i=0; i<nombre_de_ville; i++)
    {
        if(table_prim_marque[i]!=-2)
        {
            result=0;
            break;
        }
    }
    return result;
}


// on applique la fonction relacher vu en graphe;

float* relacher_table_prim_distance(float *table_prim_distance, int *table_prim_marque, int X, int Y, Ville *ville)//X est No_de_ville, Y sont des successeurs
{
    if(table_prim_marque[Y]==-2)
    {}
    else{
    if(table_prim_distance[Y]>distance(ville[X], ville[Y]))
            table_prim_distance[Y]=distance(ville[X], ville[Y]);
    }
        return table_prim_distance;
}



// on applique la fonction relacher vu en graphe qui indique qui est le père de la ville Y
int* relacher_table_prim_pere(float *table_prim_distance, int *table_prim_marque, int *table_prim_pere, int X, int Y, Ville *ville)
{
    if(table_prim_marque[Y]==-2)
    {}
    else{
    if(table_prim_distance[Y]>distance(ville[X], ville[Y]))
        {
           table_prim_pere[Y]=X;
        }
    }
        return table_prim_pere;
}


//a l'interieur de erire_fichier_chemin
void ecrire_fichier_couvrant_minimal(FILE *fp_origine_html, FILE *fp_new_html_3, int *table_prim_pere, int N, Ville *x_plus_grand_villes)
{
    char path_fichier[100];
    char ligne[100];//characteres de chaque ligne dans html
//manipulation de html, loading map.html-->map_out.html, premiere 14 lignes
    int i;
    for(i=0; i<14; i++)
    {
        fgets(ligne, 100, fp_origine_html);
        fputs(ligne, fp_new_html_3);
    }



 fprintf(fp_new_html_3, "var coordinates = [\n");
    for(i=0; i<N; i++)
    {
        fprintf(fp_new_html_3, "[%d, %.2f, %.2f], \n", i+1, x_plus_grand_villes[i].latitude, x_plus_grand_villes[i].longitude);

    }
    fprintf(fp_new_html_3, "];\n");

    fprintf(fp_new_html_3, " var edges = [\n");

     for(i=0; i<N; i++)
    {
        fprintf(fp_new_html_3, "[%d, %d], \n", i+1, table_prim_pere[i]+1);

    }

    fprintf(fp_new_html_3, "];\n");
    fprintf(fp_new_html_3, "map_center = [46.468133, 2.351074]\n\n");









//on attaque sur le fp_html_3
//for(i=0; i<N; i++){
//    if(i==0)
//    {table_prim_pere[i]=0;}
//    printf("+++%s's pere est %s+++\n", x_plus_grand_villes[i].nom_ville, x_plus_grand_villes[table_prim_pere[i]].nom_ville);
//}
//



 for(i=15; i<=29; i++)
    {
        fgets(ligne, 100, fp_origine_html);// do nothing
    }

    for(i=30; i<=86; i++)
    {
        fgets(ligne,100, fp_origine_html);
        fputs(ligne, fp_new_html_3);
    }

    rewind(fp_origine_html);
    fclose(fp_new_html_3);

}











