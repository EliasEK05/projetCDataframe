#ifndef PROJETCDATAFRAME_PROJET_H
#define PROJETCDATAFRAME_PROJET_H
#define REALOC_SIZE 256

typedef struct {
    char titre[100];
    int taille_phy;
    int taille_log;
    int* donnee;

}COLUMN;
COLUMN *create_column(char* title);

int insert_value(COLUMN* col, int value);

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int nb_occ(COLUMN* col, int val);

int position(COLUMN* col , int val);

int superieur(COLUMN* col, int val);

int inferieur(COLUMN* col, int val);

int egale(COLUMN* col, int val);









#endif //PROJETCDATAFRAME_PROJET_H
