#include <stdio.h>
#include "projet.h"

int main() {
    COLUMN * liste_ptr[100];
    int tl;
    printf("combien de colonne shouaitez vous faire?");
    scanf("%d", &tl);
    for(int i = 0; i<tl; i++){
        char title[50];
        printf("Saisir un titre de colonne : ");
        scanf("%s", title);
        COLUMN* ptr = create_column(title);
        liste_ptr[i] = ptr;
    }
    for (int i = 0; i<tl; i++){
        for (int j =0; j<tl; j++){
            printf("Saisir une valeur a ajouter dans la colonne %d ligne %d : ", i,j);
            int val;
            scanf("%d", &val);
            if (insert_value(liste_ptr[i], val) == 0)
                insert_value(liste_ptr[i], val);

        }
    }
    printf("Num colonne   ");
    for (int i = 0; i < tl; i++)
        printf("%s   ", liste_ptr[i]->titre);
    printf("\n");

    for (int i = 0; i<tl;i++){
        printf("      [%d]        ", i);
        for (int j =0; j<tl; j++) {
            printf("%d      ",liste_ptr[j]->donnee[i]);
        }
        printf("\n");
    }



    for (int i=0; i<tl; i++)
        delete_column(&liste_ptr[i]);

    return 0;
}
