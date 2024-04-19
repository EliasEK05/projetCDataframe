#include <stdlib.h>
#include "projet.h"
#include <stdio.h>

COLUMN *create_column(char* title){

    COLUMN* ptr = (COLUMN*) malloc(sizeof (COLUMN));

    ptr->taille_phy = 0;
    ptr->taille_log = 0;

    ptr->donnee = NULL;
    return ptr;
}

int insert_value(COLUMN* col, int value){
    if (col->taille_log < col->taille_phy) {
        col->donnee[col->taille_log] = value;
        col->taille_log ++;
        return 1;
    }
    else{
        col->donnee = realloc(col->donnee, REALOC_SIZE * sizeof(int));
        col->taille_phy += REALOC_SIZE;
        return 0;
    }

}

void delete_column(COLUMN **col){
    free((*col)->donnee);
    free(*col);
    *col = NULL;
}

void print_col(COLUMN* col){
    for (int i = 0; i<col->taille_log; i++){
        printf("[%d] %d\n",i, col->donnee[i]);
    }

}

int nb_occ(COLUMN* col, int val){
    int occ = 0;
    for( int i= 0; i<col->taille_log; i++){
        if (val == col->donnee[i])
            occ += 1;
    }
    return occ;
}

int position(COLUMN* col, int val){
    if (val<= col->taille_log)
        return col->donnee[val];
    else printf("il n'y a aucune valeur a cette position\n");

}

int superieur(COLUMN* col, int val){
    int cpt = 0;
    for (int i = 0; i<col->taille_log; i++){
        if (col->donnee[i] > val)
            cpt++;
    }
    return cpt;
}