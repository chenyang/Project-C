#include "../headers/MODULE_APPENDICE.h"

Ville choisir_ville_depart(char *path_fichier_ville)
{

    FILE *fp_depart;
    char depart[4];
    char line[50];
    char command1[100];
    int nombre_de_depart=0;
    int i=0;
    int NO=0;


    printf("saisir 2-4 caractere pour chercher une ville de depart: (premiere lettre en majuscule et seconde en minuscule ex: Pa)\n");
    scanf("%s", depart);
    sprintf(command1, "cat %s|grep ^%s >./depart.txt", path_fichier_ville, depart);
    system(command1);
    fp_depart=fopen("./depart.txt", "r");
    Ville *ville_depart=read_ville(fp_depart, &nombre_de_depart);

   while(ville_depart[0].pop==0)
	{	
		fclose(fp_depart);
		printf("\n\ndesole, vous n'avez pas bien choisi, try again\n\n");
		printf("entrez 1-4 caracteres de votre ville de depart (la premiere lettre en MAJ):\n");
    		scanf("%s", depart);
    		sprintf(command1, "cat %s|grep ^%s >./depart.txt", path_fichier_ville, depart);
    		system(command1);
    		fp_depart=fopen("./depart.txt", "r");
            ville_depart=read_ville(fp_depart, &nombre_de_depart);
	}


    if(ville_depart[0].pop!=0)
    {
        rewind(fp_depart);
        i=0;
        for (i=0; i<nombre_de_depart; i++)
        {
            fgets(line, 50, fp_depart);
            printf("%d.%s", i+1, line);
        }

    }




    printf("choisir le numero de la ville de depart:\n");
    scanf("%d", &NO);
    return ville_depart[NO-1];
    fclose(fp_depart);


}


Ville choisir_ville_dest(char *path_fichier_ville)
{

    FILE *fp_dest;
    char dest[4];
    char line[50];
    char command1[100];
    int nombre_de_dest=0;
    int i=0;
    int NO=0;


    printf("saisir 2-4  caractere pour chercher une ville de destination: (premiere lettre en majuscule et seconde en minuscule ex: Pa)\n");
    scanf("%s", dest);
    sprintf(command1, "cat %s|grep ^%s >./dest.txt", path_fichier_ville, dest);
    system(command1);
    fp_dest=fopen("./dest.txt", "r");
    Ville *ville_dest=read_ville(fp_dest, &nombre_de_dest);


    while(ville_dest[0].pop==0)
	{
		fclose(fp_dest);
		printf("\n\ndesole, vous n'avez pas bien choisi, try again\n\n");
		printf("entrez 1-4 caracteres de votre ville de destination (la premiere lettre en MAJ):\n");
    		scanf("%s", dest);
    		sprintf(command1, "cat %s|grep ^%s >./dest.txt", path_fichier_ville, dest);
    		system(command1);
    		fp_dest=fopen("./dest.txt", "r");
            ville_dest=read_ville(fp_dest, &nombre_de_dest);

	}

    if(ville_dest[0].pop!=0)
    {
        rewind(fp_dest);
        i=0;
        for (i=0; i<nombre_de_dest; i++)
        {
            fgets(line, 50, fp_dest);
            printf("%d.%s", i+1, line);
        }


    }

    printf("choisir le numero comme le dest:\n");
    scanf("%d", &NO);
    return ville_dest[NO-1];
    fclose(fp_dest);

}


