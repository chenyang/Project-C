#include "../headers/MODULE_FICHIER.h"

float change_format(char* str)
{
    char* str_new;  //nouvelle chaine qui ne contiendra pas la dernière lettre
    str_new=(char*)malloc(50*sizeof(char));
    float finale;

    int i=0;
    while((str[i] != 'S' && str[i] != 'W' && str[i] != 'N' && str[i] != 'E') && i<50)
    {
        str_new[i]=str[i];
        i++;

    }
    str_new[i]='\0';// pour enlever la lettre et permettre au atof DE FONCTIONNER !!!
    switch (str[i])
    {
    case 'S':
    case 'W':
        //printf("je traite les S et W");
        finale= (atof(str_new) * (-1.0));
        break;
    default:
        //printf("Je suis dans default");
        finale=atof(str_new);
        break;
    }
     free(str_new);
    return finale;// renvoie les bonnes coordonnées

}



FILE* lire_fichier(char* path_fichier)
{
    FILE *fp_ville;
    //char *path_fichier[100];//le path de fichie

    //on lit le path_fichier de fp_ville
    fp_ville=fopen(path_fichier, "r");
    if(fp_ville==NULL)
    { printf("le fichier n'exite pas, on exit le programe\n\n"); exit(0);}
    else{
    printf("le fichier existe\n");
    return fp_ville;
    }
}

//fin outils

//les fonctionalites
Ville* read_ville(FILE* fp, int* nombre_de_ville)// il faut tester
{

    FILE* fp_ville;
    fp_ville=fp;

    char *line=(char*)malloc(100*sizeof(char));//les caractere d'une ligne
    char c;
    //compter combien de villes y a-t-il?
    while(!feof(fp_ville))
    {
        c=fgetc(fp_ville);
        if(c=='\n')
        *nombre_de_ville=*nombre_de_ville+1;
    }

    printf("le nombre de ville est:%d\n", *nombre_de_ville);

    Ville *ville=(Ville*)malloc(*nombre_de_ville*sizeof(Ville));
    rewind(fp_ville);
    int i;
    for(i=0; i<*nombre_de_ville; i++)
    {
            fgets(line, 100, fp_ville);
            char *token;
            token=strtok(line, ",");
            while(token!=NULL)
            {
                strcpy(ville[i].nom_ville,token); //printf("%s", ville[i].nom_ville); printf("+++%s\n", token);
                token = strtok( NULL, "," );
                ville[i].pop=atoi(token); //printf("%d", ville[i].pop); printf("+++%s\n", token);
                token = strtok( NULL, "," );
                ville[i].latitude=change_format(token); //printf("%f", ville[i].latitude); printf("+++%s\n", token);
                token = strtok( NULL, "," );
                ville[i].longitude=change_format(token); //printf("%f\n", ville[i].longitude); //printf("+++%s\n", token);
                token = strtok( NULL, "," );
            }

    }
	free(line);
    return ville;
    rewind(fp_ville);

}


void ecrire_fichier(Ville *ville, FILE *fp_origine_html, FILE *fp_new_html, int x)
{
    char ligne[100];//characteres de chaque ligne dans html


//manipulation de html, loading map.html-->map_out.html, premiere 14 lignes
    int i;
    for(i=0; i<14; i++)
    {
        fgets(ligne, 100, fp_origine_html);
        fputs(ligne, fp_new_html);
    }



//on attaque sur .html
    fprintf(fp_new_html, "var coordinates = [\n");
    for(i=0; i<x; i++)
    {
        fprintf(fp_new_html, "[%d, %.2f, %.2f], \n", i+1, ville[i].latitude, ville[i].longitude);

    }
    fprintf(fp_new_html, "];\n");

    fprintf(fp_new_html, " var edges = [\n");

    for(i=1; i<x; i++)
    {
        fprintf(fp_new_html, "[%d, %d], \n", i, i+1);

    }
    fprintf(fp_new_html, "];\n");
    fprintf(fp_new_html, "map_center = [46.468133, 2.351074]\n\n");



    for(i=15; i<=29; i++)
    {
        fgets(ligne, 100, fp_origine_html);// do nothing
    }

    for(i=30; i<=86; i++)
    {
        fgets(ligne,100, fp_origine_html);
        fputs(ligne, fp_new_html);
    }

    fclose(fp_new_html);
    rewind(fp_origine_html);
}
