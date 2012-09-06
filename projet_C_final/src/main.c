#include"./headers/MODULE_GLOBALE.h"
#include"./headers/MODULE_FICHIER.h"
#include"./headers/MODULE_ARBRE.h"
#include"./headers/MODULE_DIJKSTRA.h"
#include"./headers/MODULE_APPENDICE.h"

int main()
{

    char path_fichier[100] ;	// adresse du fichier a lire
    char path_fichier_ville[100];	// adresse du fichier de villes
    FILE *fp_ville;	// fichier de villes
    FILE *fp_origine_html;	// fichier donne map.html
    FILE *fp_new_html;		// fichier cree map.html pour l'option 1
    FILE *fp_new_html_2;	// fichier cree map.html pour l'option 2
    FILE *fp_new_html_3;	// fichier cree map.html pour l'option 3
    int x=0;	//nombre de villes a afficher
    int i=0;	//compteur
    int nombre_de_ville=0;//le nombre de ville du fichier
    int limite=0;	// limite de parcours de l'avion
    int No_de_ville_X;	//Ville_X
    int No_de_ville_Y;	//succeseur de X
    float *table_distance;	//tableau des distances dans DIJKSTRA
    int *table_marque;	//tableau des marques dans DIJKSTRA
    int *table_pere;	//tableau des peres dans DIJKSTRA
    float *table_prim_distance;	//tableau des distances dans Prim
    int *table_prim_marque;	//tableau des marques dans Prim
    int *table_prim_pere;	//tableau des peres dans Prim
    int No_de_depart=0;	//numero de la ville de depart
    int No_de_dest=0;	//numero de la ville de destination
    Ville *ville;	//tableau des villes
    Ville depart;	//ville de depart
    Ville dest;		//ville de destination
    int N;	//le numero demonstre les N plus grandes villes pour afficher aerien couvrant
    Ville *x_plus_grand_villes;	//les x plus grandes villes
    char choix_menu;	// caractere pour choisir dans le menu
    char command1[100];	//commande pour utiliser la commande systeme
    char command2[100];	//commande pour utiliser la commande systeme
    char Continue_encore[100];	//caractere pour continuer le menu
    int trouvee=0;	//valeur pour trouver la ville

do{
    do
    {	
	//menu

    printf("\n\nBIENVENUE DANS LE PROGRAMME D'UTILISATION DES DONNEES GEOLOCALISES DU GROUPE 5: DILI5 (地理)\n\n\n\t\tMENU PRINCIPAL:\n\n\t");
    printf("Veuillez choisir l'option que vous désirez réaliser:\n\n\n");
    printf("1: Afficher les X plus grandes villes sur google map\n\n2: Calculer le plus court chemin entre deux villes\n\n3: Calculer l'arbre aérien recouvrant minimal\n\n");
    scanf("%c",&choix_menu);

    if (choix_menu != '1' && choix_menu != '2' && choix_menu != '3') printf("entrez une option valide ! ");

    }while(choix_menu != '1' && choix_menu != '2' && choix_menu != '3');


    //lire fichier_ville
    printf("saisir le path de ville_fichier:\n");
    scanf("%s", path_fichier_ville);

    switch(choix_menu)
    {
        case '1':
        printf("vous avez choisit d'afficher les X premières villes sur google map\n");

    //*******************************************Questions 1**************************************************

	nombre_de_ville=0; // pour reinitialiser le menu a chaque fois

       if(path_fichier_ville[strlen(path_fichier_ville)-4]=='.' && path_fichier_ville[strlen(path_fichier_ville)-3]=='x' && path_fichier_ville[strlen(path_fichier_ville)-2]=='m' && path_fichier_ville[strlen(path_fichier_ville)-1]=='l')
       {
	// avec un fichier xml
        sprintf(command1, "./parser.out %s > ville_antlr.csv", path_fichier_ville);
        system(command1);	// commande system qui applique la commande1
        fp_ville=lire_fichier("./ville_antlr.csv");	
       }
       else
       {
	// avec un fichier csv
        fp_ville=lire_fichier(path_fichier_ville);
       }

       //lire fichier map.html
        printf("saisir le path_fichier de map.html\n");
        scanf("%s", path_fichier);
        fp_origine_html=lire_fichier(path_fichier);
        
	//lire fichier map_out.html
        printf("saisir le path_fichier de map_out.html:\n");
        scanf("%s", path_fichier);
        fp_new_html=fopen(path_fichier, "w+");


        ville=read_ville(fp_ville, &nombre_de_ville);


    //*******************************************Question 2************************************************
  
        //affiche_tableau(ville, 50);
        printf("saisir X premieres villes:\n");
        scanf("%d", &x);
        while(x>nombre_de_ville||x<=0)
        {
	printf("respectez la regle, try again\n");
        scanf("%d", &x);
        }
        ville=tri_ville(ville, 1, nombre_de_ville);	//tri decroissant
        x_plus_grand_villes=x_premieres_villes(ville, x);	// choix des villes
        ecrire_fichier(x_plus_grand_villes, fp_origine_html, fp_new_html, x);	//ecriture du fichier
        printf("\n\nfichier map_out done =)\n\n");
    //-----------------------------------------------------------------------------------------
	
	// liberation de l'espace memoire du tableau dynamique des villes
	free(ville);
	fclose(fp_origine_html);
        break;

        case '2':

	nombre_de_ville=0;


        printf("vous avez choisit de calculer le plus court chemin entre deux villes\n");

       if(path_fichier_ville[strlen(path_fichier_ville)-4]=='.' && path_fichier_ville[strlen(path_fichier_ville)-3]=='x' && path_fichier_ville[strlen(path_fichier_ville)-2]=='m' && path_fichier_ville[strlen(path_fichier_ville)-1]=='l')
       {
        sprintf(command1, "./parser.out %s > ville.csv", path_fichier_ville);
        system(command1);
        fp_ville=lire_fichier("./ville_antlr.csv");


        //**********************************************Question3+Bonus 1*******************************************
        depart=choisir_ville_depart("./ville_antlr.csv");
        dest=choisir_ville_dest("./ville_antlr.csv");
        while(depart.pop==0 || dest.pop==0)
        {
        printf("\ndesole :( vous devez respectez la facon de saisir, try again:\n\n");
        depart=choisir_ville_depart("./ville_antlr.csv");
        dest=choisir_ville_dest("./ville_antlr.csv");
        }
        printf("le ville depart:%s\n",depart.nom_ville);
        printf("le ville dest:%s\n", dest.nom_ville);
        printf("la distance direct entre ces 2 villes est:%f\n", distance(depart, dest));
        //----------------------------------------------------------------------------------
       }
       else
       {
        fp_ville=lire_fichier(path_fichier_ville);

        //**********************************************Question3+Bonus 1*******************************************
        depart=choisir_ville_depart(path_fichier_ville);
        dest=choisir_ville_dest(path_fichier_ville);
        while(depart.pop==0 || dest.pop==0)
        {
        printf("\ndesole :( vous devez respectez le facon de saisir, try again:\n\n");
        depart=choisir_ville_depart(path_fichier_ville);
        dest=choisir_ville_dest(path_fichier_ville);
        }
        printf("le ville depart:%s\n",depart.nom_ville);
        printf("le ville dest:%s\n", dest.nom_ville);
        printf("la distance direct entre ces 2 villes est:%f\n", distance(depart, dest));
        //--------------------------------------------------------------------------------------
       }

              //lire fichier map.html
        printf("saisir le path_fichier de map.html\n");
        scanf("%s", path_fichier);
        fp_origine_html=lire_fichier(path_fichier);

        //lire fichier map_out.html
        printf("saisir le path_fichier de map_out_2.html:\n");
        scanf("%s", path_fichier);
        fp_new_html_2=fopen(path_fichier, "w+");


        //--------------------------------------------------Question3_Dijkstra----------------------------------------
        //initiation les tableau: distance, marque et pere

        ville=read_ville(fp_ville, &nombre_de_ville);
        table_distance=creer_table_distance(depart, ville, nombre_de_ville);
        table_marque=creer_table_marque(nombre_de_ville);
        table_pere=creer_table_pere(nombre_de_ville);
        printf("saisir la limite de longeur:\n");
        scanf("%d", &limite);


        //----------------------------------------Dijkstra----------------------------------------------------------
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
                    if(distance(ville[No_de_ville_X], ville[No_de_ville_Y])<=limite)//pour les successeurs de ville_X
                    {
                        //Attention!! ici l'ordre des fonctions est un peu different de l'algorithme du cours
                        //si on utilise relache table_distance en premier, la fonction relacher_table_pere ne marche bien!!
                        //il faut, premierement, je notes les peres; Ensuite, on applique relacher_table_distance//
                        table_pere=relacher_table_pere(table_distance, table_pere, No_de_ville_X, No_de_ville_Y, ville);
                        table_distance=relacher_table_distance(table_distance, No_de_ville_X, No_de_ville_Y, ville);
                    }
                }
            }
        }
        ////pour le tester
        //for(i=0; i<nombre_de_ville; i++){
        //    printf("%d. %s---%s---> %f, %d\n", i, depart.nom_ville, ville[i].nom_ville, table_distance[i], table_marque[i]);}
        //for(i=0; i<nombre_de_ville; i++){
        //    if(table_pere[i]==-1)
        //    {continue;}
        //    else{printf("%d. %s's father is %s-\n", i, ville[i].nom_ville, ville[table_pere[i]].nom_ville);
        //    }
        //}

        //！！！不建立图很好！！至少不用1000*10000建图  每两城市之间城市数目《1000！！ (avec un graphe il faut faire un calcul de 1000*1000 alors qu'ici on utilise 1000)
        //建图与不建图比较！不建图比较好


        for(i=0; i<nombre_de_ville; i++)	
        {
            if(ville[i].latitude==depart.latitude&&ville[i].longitude==depart.longitude)
                No_de_depart=i;
            if(ville[i].latitude==dest.latitude&&ville[i].longitude==dest.longitude)
                No_de_dest=i;
        }


        printf("apres Dijkstra, la distance entre ces 2 villes est: %f\n", table_distance[No_de_dest]);

        if(table_distance[No_de_dest]!=99999.0&&table_distance[No_de_dest]!=0.0)
        {
            ecrire_fichier_chemin(ville, fp_origine_html, fp_new_html_2, table_pere, No_de_depart, No_de_dest);
            printf("ecrire map_chemin_done =) \n\n");
        }
        else
        {
        printf("on ne peut pas y arriver ou alors vous avez saisi deux fois la meme ville\n\n");
        }

	//liberation des espaces memoire des tableaux dynamiques
	free(table_distance);	 
	free(table_marque);
	free(table_pere);
	free(ville);
	fclose(fp_origine_html);


        break;

    //-----------------------------------------------------------------------------------------------------------------------

        case '3':

        printf("vous avez choisit de calculer l'arbre aérien recouvrant minimal\n");

	nombre_de_ville=0;

        if(path_fichier_ville[strlen(path_fichier_ville)-4]=='.' && path_fichier_ville[strlen(path_fichier_ville)-3]=='x' && path_fichier_ville[strlen(path_fichier_ville)-2]=='m' && path_fichier_ville[strlen(path_fichier_ville)-1]=='l')
       {
        sprintf(command1, "./parser.out %s > ville.csv", path_fichier_ville);
        system(command1);
        fp_ville=lire_fichier("./ville_antlr.csv");
       }
        else
       {
        fp_ville=lire_fichier(path_fichier_ville);
       }

              //lire fichier map.html

        printf("saisir le path_fichier de map.html\n");
        scanf("%s", path_fichier);
        fp_origine_html=lire_fichier(path_fichier);

        //lire fichier map_out.html
        printf("saisir le path_fichier de map_out_3.html:\n");
        scanf("%s", path_fichier);
        fp_new_html_3=fopen(path_fichier, "w+");




        //***********************************************Question 4 Prim***********************************************************

        //initiation les tableau: distance, marque et pere
	ville=read_ville(fp_ville, &nombre_de_ville);
        printf("saisir les N plus grand villes pour afficher l'arbre aerien couvrant, au moins 1 villes..!:\n");
        scanf("%d", &N);
        while(N>nombre_de_ville||N<=0)
        {
            printf("Vous ne respectez pas la regle, try again\n");
            scanf("%d", &N);
        }
        ville=tri_ville(ville, 1, nombre_de_ville);
        x_plus_grand_villes=x_premieres_villes(ville, N);
        
	//affiche_tableau(x_plus_grand_villes, N); possibilite d'afficher le tableau

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
        //pour le tester
        //    for(i=0; i<N; i++){
        //    printf("%f  %d\n", table_prim_distance[i], table_prim_marque[i]);
        //    }
        }
        //pour le tester
        //for(i=0; i<N; i++){
        //    printf("%f\n", table_prim_distance[i]);
        //}
        //
        //for(i=0; i<N; i++){
        //    printf("+++%s's pere est %s+++\n", x_plus_grand_villes[i].nom_ville, x_plus_grand_villes[table_prim_pere[i]].nom_ville);
        //}

        ecrire_fichier_couvrant_minimal(fp_origine_html, fp_new_html_3, table_prim_pere, N, x_plus_grand_villes);
        printf("\n\necrire fichier fichier_couvrant_minimal done =)\n\n");
	
	//liberation des espaces memoire des tableaux dynamiques
	fclose(fp_origine_html);
	free(table_prim_distance);
	free(table_prim_marque);
	free(table_prim_pere);
	free(ville);
        break;

        default:

        printf("erreur vous n'avez pas selectionner le bon numéro !!!\n");
        break;
    }


    sprintf(command2, "rm -f ville_antlr.csv");
    system(command2);

    printf("voulez vous continuer ?\n N pour arreter\n");
    scanf("%s",Continue_encore);

    printf("Vous avez taper: %s\n",Continue_encore);

    if (*Continue_encore =='N' || *Continue_encore=='n')
    { 
    	printf("FIN DU PROGRAMME\n");
    }

    printf("\n\n\n");

}while(*Continue_encore!='N' && *Continue_encore!='n');

return 0;
}


