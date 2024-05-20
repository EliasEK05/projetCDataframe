#ifndef PROJETCDATAFRAME_PROJET_H
#define PROJETCDATAFRAME_PROJET_H
#define REALOC_SIZE 256

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum enum_type
{
    NULLVAL = 0 ,INT , CHAR, FLOAT, DOUBLE, STRING,  UINT,  STRUCTURE
}; typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}; typedef union column_type COL_TYPE ;

typedef struct {
    char* titre;
    unsigned taille_phy;
    unsigned int taille_log;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
    // index valid
    // 0 : no index
    // -1 : invalid index
    // 1 : valid index
    int valid_index;
    // direction de tri Ascendant ou Déscendant
    // 0 : ASC
    // 1 : DESC
    int sort_dir;
}COLUMN;

//focntions pour une colonne :
COLUMN *create_column(ENUM_TYPE type, char *title);
int insert_value(COLUMN *col, void *value);
void print_col(COLUMN* col);
void delete_column(COLUMN **col);

//fonctions concernant le CDT :
COLUMN** cdt(int nb_col);
COLUMN** cdt_vide(int nb_col);  // pas encore utilisé
void convert_value(COLUMN *col, int i, char *str, int size);
void affichage_cdt(COLUMN** liste, int nb_col);
void delete_cdt(COLUMN** liste, int nb_col);

//fonctions pour les fonctionalité:
void affichage_cdt_ligne(COLUMN** liste, int nb_col, int debut, int fin);
void affichage_cdt_col(COLUMN** liste, int nb_col, int debut, int fin);
void add_line(COLUMN** liste, int taille);
void add_col(COLUMN*** liste, int *taille);
void suppr_ligne(COLUMN** liste, int taille);
void suppr_col(COLUMN*** liste, int *taille );
void renommer_col(COLUMN** liste, int taille);
int rechercher_val(COLUMN** liste, int taille);
void remplacer_valeur(COLUMN** liste, int taille);

//fonctions pour le tri :
void permuter(int *a, int *b);
void quicksort(COLUMN *col, int first, int last) ;
int partition(COLUMN *col, int gauche, int droite);
void tri_par_insertion(COLUMN *col);
int compare(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type);
void affichage_par_index(COLUMN** liste, int taille);



#endif //PROJETCDATAFRAME_PROJET_H

