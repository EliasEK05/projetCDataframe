#include "projet.h"


int main() {
    printf("Bienvenu dans le concepteur de CDataframe\nVoulez vous remplir votre Dataframe par saisie utilisateur(0) ou en dur(1)?\n");
    int remplissage;
    COLUMN** liste_ptr;
    int taille;

    scanf("%d", &remplissage);
    if (remplissage == 0){

        printf("Saisir le nombre de colonne souhaite dans le CDataframe: ");
        scanf("%d", &taille);printf("\n");
        liste_ptr = cdt(taille);
        affichage_cdt(liste_ptr, taille);



    }
    else{
        if (remplissage == 1){
            taille = 5;
            liste_ptr = malloc(taille * sizeof(COLUMN*));
            liste_ptr[0] = create_column(STRING, "col_int");
            liste_ptr[1] = create_column(CHAR, "col_char");
            liste_ptr[2] = create_column(FLOAT, "col_float");
            liste_ptr[3] = create_column(DOUBLE, "col_double");
            liste_ptr[4] = create_column(INT, "col_string");

            int val[] = {145, 5, 10, 2, 0};
            char caractere[] = {'a', 'j', 'l', 'g', 'b'};
            float val2[] = {15.5, 18.9, 1.2, 0.2, 17.4};
            double val3[] = {15.5, 18.9, 1.2, 0.2, 17.4};
            char* mot[] = {"mot1", "Elias", "gnome","zebre", "arbre"};
            for (int i =0; i<4; i++ ){                                  //Veillez ajuster la limite de la boucle en focntion du nombre de ligne
                insert_value(liste_ptr[0], mot[i]);
                insert_value(liste_ptr[1], &caractere[i]);
                insert_value(liste_ptr[2], &val2[i]);
                insert_value(liste_ptr[3], &val3[i]);
                insert_value(liste_ptr[4], &val[i]);
                }
            insert_value(liste_ptr[0], mot[4]);
            insert_value(liste_ptr[1], &caractere[4]);
            insert_value(liste_ptr[2], &val2[4]);
            insert_value(liste_ptr[3], &val3[4]);
            insert_value(liste_ptr[4], NULL);
            affichage_cdt(liste_ptr, taille);





        }
        else
            printf("Valeur non reconnue, veillez saisir 1 ou 0");
    }



    int continuer = 1;
    while(continuer) {
        printf("\n\nLes fonctionnalites possible: \n");
        printf("    1.Afficher une partie des lignes du CDataframe selon une limite fournie\n");
        printf("    2.Afficher une partie des colonnes du CDataframe selon une limite fournie\n");
        printf("    3.Afficher le CDataframe complet\n");
        printf("    4.Afficher une seule colonne\n");
        printf("    5.Ajouter une ligne de valeurs au CDataframe\n");
        printf("    6.Ajouter une colonne de valeurs au CDataframe\n");
        printf("    7.Supprime une ligne de valeurs au CDataframe\n");
        printf("    8.Supprime une colonne de valeurs au CDataframe\n");
        printf("    9.Renommer le titre d une colonne du CDataframe\n");
        printf("    10.Verifier l existence d une valeur (recherche) dans le CDataframe\n");
        printf("    11.Remplacer une valeur du CDataframe\n");
        printf("    12.Afficher le noms des colonnes\n");
        printf("    13.Afficher le nombre de lignes du CDataframe\n");
        printf("    14.Afficher le nombre de colonnes du CDataframe\n");
        printf("    15.Tri des index d'une colonne\n");
        printf("    16.Afficher le CDataframe par index\n");
        int fonctionnate ;
        printf("\nChoisissez une fonctionnalite : ");
        scanf("%d", &fonctionnate);


        switch (fonctionnate) {

            case 1:{
                printf(""); // pour éviter que l'IDE ne détecte une erreur de synthaxe. Seul moyen que j'ai trouvé pour que ca marche
                int fin;
                int debut;
                do {
                    printf("\nSaisir les bornes des lignes affiches compris entre 0 et %d [debut, fin]: ",liste_ptr[0]->taille_log - 1);
                    scanf("%d,%d", &debut, &fin);
                } while (debut < 0 || fin >= liste_ptr[0]->taille_log - 1);
                affichage_cdt_ligne(liste_ptr, taille, debut, fin);
                break;
            }
            case 2:{
                int debut, fin;
                do{
                    printf("\nSaisir les bornes des colonnes affiches compris entre 0 et %d [debut, fin]: ", taille-1);
                    scanf("%d,%d", &debut, &fin);
                } while (debut < 0 || fin >= taille-1);
                affichage_cdt_col(liste_ptr, taille, debut, fin);
                break;
            }
            case 3:{
                affichage_cdt(liste_ptr, taille);
                break;
            }
            case 4:{
                int col;
                do{
                printf("\nSaisissez le numero de la colonne que vous souhaitez afficher: ");
                scanf("%d", &col);} while (col<0 || col>taille-1);
                printf("\n");
                print_col(liste_ptr[col]);
                break;
            }
            case 5:{
                add_line(liste_ptr, taille);
                for (int i=0; i<taille; i++)
                    liste_ptr[i]->valid_index = 2;
                break;
            }
            case 6:{
                add_col(&liste_ptr, &taille);
                break;
            }
            case 7:{
                suppr_ligne(liste_ptr, taille);
                for (int i=0; i<taille; i++)
                    liste_ptr[i]->valid_index = 2;
                break;
            }
            case 8:{
                suppr_col(&liste_ptr, &taille);
                break;
            }
            case 9:{
                renommer_col(liste_ptr, taille);
                break;
            }
            case 10:{
                int verif = rechercher_val(liste_ptr, taille);
                break;
            }
            case 11:{
                remplacer_valeur(liste_ptr, taille);
                break;
            }
            case 12:{
                printf("\nle nom des colonnes sont: \n");
                for (int i = 0; i<taille; i++){
                    printf("[%d] %s\n", i,  liste_ptr[i]->titre);
                }
                break;
            }
            case 13:{
                printf("\nLe nombre de ligne du CDataframe est %d", liste_ptr[0]->taille_log);
                break;
            }
            case 14:{
                printf("\nLe nombre de colonne du CDataframe est %d", taille);
                break;
            }
            case 15:{
                printf("\nSaisir la colonne que vous voulez trier : ");
                int col;
                scanf("%d", &col);
                if (col >= 0 && col < taille) {
                    if (liste_ptr[col]->valid_index == 0) {
                        quicksort(liste_ptr[col], 0, liste_ptr[col]->taille_log - 1);
                        liste_ptr[col]->valid_index = 1;
                    }
                    else{
                        if(liste_ptr[col]->valid_index == 1)
                            printf("\nColonne deja triee");
                        if(liste_ptr[col]->valid_index == 2){
                            tri_par_insertion(liste_ptr[col]);
                            liste_ptr[col]->valid_index = 1;
                        }

                    }
                } else {
                    printf("\nColonne invalide.\n");
                }
                break;
            }
            case 16:{
                affichage_par_index(liste_ptr, taille);
                break;
            }
            case 0:
                continuer = 0;
                break;
        }


    }
    delete_cdt(liste_ptr, taille);
    free(liste_ptr);
    return 0;
}


