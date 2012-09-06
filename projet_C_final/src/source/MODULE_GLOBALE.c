#include "../headers/MODULE_GLOBALE.h"
#define PI 3.1415926

float distance(Ville ville1, Ville ville2)/*utilisee ds MODULE_DIJKSTRA et MODULE_ARBRE_COUVRANT*/
{

        float R = 6371.0; // km
        float lat1=ville1.latitude;
        float lat2=ville2.latitude;
        float lon1=ville1.longitude;
        float lon2=ville2.longitude;

        float d = acos(sin(lat1*PI/180.0)*sin(lat2*PI/180.0) + cos(lat1*PI/180.0)*cos(lat2*PI/180.0) *cos((lon2-lon1)*PI/180.0)) * R;
        return d;
}


void affiche_tableau(Ville* ville, int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        printf("%s, %f, %f\n", ville[i].nom_ville, ville[i].latitude, ville[i].longitude);
    }
}


Ville* tri_ville(Ville *ville, int flag, int nombre_de_ville)
{

        //printf("il y a %d villes\n", nombre_de_ville);// il a
        if(flag==1)//si vrai, alors tri_croissant
            {
                    int i=nombre_de_ville;// we know it..
                    int j;
                    for(i=nombre_de_ville; i>0; i--)
                    {
                        for(j=0; j<i-1; j++)
                        {
                            if(ville[j].pop<ville[j+1].pop)
                            {
                                //printf("ici, ville[%d].pop=%d, ville[%d].pop=%d\n", j, ville[j].pop, j+1, ville[j+1].pop);
                                Ville temp;
                                temp=ville[j];
                                ville[j]=ville[j+1];
                                ville[j+1]=temp;
                            }
                        }
                    }
            }
          else{//si faux, alors tri_decroissant
                    int i=nombre_de_ville;// we know it..
                    int j;
                    for(i=nombre_de_ville; i>0; i--)
                    {
                        for(j=0; j<i-1; j++)
                        {
                            if(ville[j].pop>ville[j+1].pop)
                            {
                                //printf("ici, ville[%d].pop=%d, ville[%d].pop=%d\n", j, ville[j].pop, j+1, ville[j+1].pop);
                                Ville temp;
                                temp=ville[j];
                                ville[j]=ville[j+1];
                                ville[j+1]=temp;
                            }
                        }
                    }
            }

        return ville;
}

Ville* x_premieres_villes(Ville *ville_triee, int x)
{
    int i=0;
    Ville *x_premieres_villes;// x premieres villes
        for(i=0; i<x; i++)
        {
            x_premieres_villes=ville_triee;
            //printf("---%d---\n", x_premieres_villes->pop); pour tester
            ville_triee++;
            x_premieres_villes++;
        }

        //restore pointeur
        for(i=0; i<x; i++)
        {
         x_premieres_villes--;
        }

//pour les tester
//        printf("les x plus grand nombre d'habitant sont:\n");
//        for(i=0; i<x; i++)
//        {
//            printf("%s, %f, %f, %d\n", x_premieres_villes[i].nom_ville, x_premieres_villes[i].latitude, x_premieres_villes[i].longitude, x_premieres_villes[i].pop);
//        }

        return x_premieres_villes;

}
