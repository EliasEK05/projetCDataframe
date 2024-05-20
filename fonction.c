#include "projet.h"




COLUMN *create_column(ENUM_TYPE type, char* title){

    COLUMN* ptr = (COLUMN*) malloc(sizeof (COLUMN));
    ptr->titre = malloc(strlen(title) + 1);
    strcpy(ptr->titre, title);
    ptr->taille_phy = 0;
    ptr->taille_log = 0;
    ptr->column_type = type;
    ptr->data = NULL;
    ptr->index = NULL;
    ptr->valid_index = 0;
    return ptr;
}

int insert_value(COLUMN* col, void *value) {
    if (col->taille_log >= col->taille_phy) {
        col->taille_phy += REALOC_SIZE;
        col->data = (COL_TYPE**)realloc(col->data, col->taille_phy * sizeof(COL_TYPE*));
        col->index = (unsigned long long int*)realloc(col->index, col->taille_phy * sizeof(unsigned long long int));
        for (int i = col->taille_log; i < col->taille_phy; i++) {
            col->data[i] = NULL;
            col->index[i] = i;
        }
    }

    if (value == NULL) {
        col->data[col->taille_log] = NULL;
    } else {
        col->data[col->taille_log] = (COL_TYPE*)malloc(sizeof(COL_TYPE));
        switch (col->column_type) {
            case INT:
                col->data[col->taille_log]->int_value = *((int*)value);
                break;
            case CHAR:
                col->data[col->taille_log]->char_value = *((char*)value);
                break;
            case FLOAT:
                col->data[col->taille_log]->float_value = *((float*)value);
                break;
            case DOUBLE:
                col->data[col->taille_log]->double_value = *((double*)value);
                break;
            case STRING:
                col->data[col->taille_log]->string_value = (char*)malloc(strlen((char*)value) + 1);
                strcpy(col->data[col->taille_log]->string_value, (char*)value);
                break;
            default:
                free(col->data[col->taille_log]);
                return 0;
        }
    }
    col->index[col->taille_log] = col->taille_log;
    col->taille_log++;
    return 1;
}


void delete_column(COLUMN **col) {
    if (*col) {
        for (int i = 0; i < (*col)->taille_log; i++) {
            if ((*col)->column_type == STRING && (*col)->data[i]) {
                free((*col)->data[i]->string_value);
            }
            free((*col)->data[i]);
        }
        free((*col)->data);
        free((*col)->index);
        free((*col)->titre);
        free(*col);
        *col = NULL;
    }
}

void convert_value(COLUMN *col, int i, char *str, int size){
        if (col->data[i] == NULL) {
            strncpy(str, "NULL", size);
            str[size - 1] = '\0';
        } else {
            switch (col->column_type) {
                case INT:
                    snprintf(str, size, "%d", col->data[i]->int_value);
                    break;
                case CHAR:
                    snprintf(str, size, "%c", col->data[i]->char_value);
                    break;
                case FLOAT:
                    snprintf(str, size, "%.2f", col->data[i]->float_value);
                    break;
                case DOUBLE:
                    snprintf(str, size, "%.2f", col->data[i]->double_value);
                    break;
                case STRING:
                    strncpy(str, col->data[i]->string_value, size);
                    str[size - 1] = '\0';
                    break;
                default:
                    str[0] = '\0';
                    break;
            }
        }
    }


void print_col(COLUMN* col){
    printf("Affichage de la colonne '%s':\n", col->titre);
    char str[100];
    for (int i = 0; i<col->taille_log; i++){
        if (col->data[i] == NULL){
            printf("[%d] NULL\n", i);
        }
        else{
        convert_value(col, i, str, sizeof(str));
        printf("[%d] %s \n",i, str);}
    }

}

void affichage_cdt(COLUMN** liste, int nb_col) {
    if (nb_col == 0) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    char str[100];
    printf("Affichage du CDataframe :\n\n");

    for (int i = 0; i < liste[0]->taille_log; i++) { // ligne
        printf("[%d]\t", i);
        for (int j = 0; j < nb_col; j++) {
            COLUMN *col = liste[j];
            if (col->data[i] == NULL) {
                printf("NULL\t");
            } else {
                convert_value(col, i, str, sizeof(str));
                printf("%s\t", str);
            }
        }
        printf("\n");
    }
}



COLUMN** cdt(int nb_col) {
    COLUMN **liste_col = malloc(nb_col * sizeof(COLUMN*));
    int type;
    char titre[100];


    for (int i = 0; i < nb_col; i++) {
        printf("Type de la colonne, ecrivez 1 pour int, 2 pour char, 3 pour float, 4 pour double, 5 pour str :");
        scanf("%d", &type);printf("\n");
        printf("Saisir un titre : ");

        scanf("%s", titre);printf("\n");

        liste_col[i] = create_column(type, titre);
    }

    int nb_val;
    printf("Saisir le nombre de valeur souhaite dans les colonnes :");
    scanf("%d", &nb_val);printf("\n");

    for(int i = 0; i<nb_col; i++){
        for (int j = 0; j<nb_val; j++){
            printf("\nSaisir la valeur %d de la colonne %d :", j, i);
            char input[100];
            scanf("%s", input);
            if (strcmp(input, "NULL") == 0) {
                insert_value(liste_col[i], NULL);}
            else {
                switch (liste_col[i]->column_type) {
                    case INT: {
                        int val = atoi(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case CHAR: {
                        char val = input[0];
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case FLOAT: {
                        float val = atof(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case DOUBLE: {
                        double val = atof(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case STRING: {
                        insert_value(liste_col[i], input);
                        break;
                    }


                }
            }


        }
    }

    return liste_col;
}


COLUMN** cdt_vide(int nb_col){
    COLUMN **liste_col = malloc(nb_col * sizeof(COLUMN*));
    int type;
    char titre[100];


    for (int i = 0; i < nb_col; i++) {
        printf("Type de la colonne, ecrivez 1 pour int, 2 pour char, 3 pour float, 4 pour double, 5 pour str :");
        scanf("%d", &type);printf("\n");
        printf("Saisir un titre : ");

        scanf("%s", titre);printf("\n");

        liste_col[i] = create_column(type, titre);
    }
    return liste_col;
}







void delete_cdt(COLUMN** liste, int nb_col){
    for (int i=0; i<nb_col; i++)
        delete_column(&liste[i]);
}



void affichage_cdt_ligne(COLUMN** liste, int nb_col, int debut, int fin){
    char str[100];
    printf("Affichage du CDataframe :\n\n");
    for(int i=debut; i<=fin; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=0; j<nb_col; j++){
            COLUMN *col = liste[j];
            if (col->data[i] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, i, str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}

void affichage_cdt_col(COLUMN** liste, int nb_col, int debut, int fin){
    char str[100];
    printf("Affichage du CDataframe :\n\n");
    for(int i=0; i<liste[i]->taille_log; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=debut; j<=fin; j++){
            COLUMN *col = liste[j];
            if (col->data[i] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, i, str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}


void add_line(COLUMN** liste, int taille){
    for (int i=0; i<taille; i++){
        switch (liste[i]->column_type) {
            case INT: {
                int val;
                printf("\nSaisissez l'entier souhaitez vous ajouter (int) : ");
                scanf("%d", &val);
                insert_value(liste[i], &val);
                break;
            }
            case CHAR: {
                char val;
                printf("\nSaisissez le charactere souhaitez vous ajouter (char) : ");
                scanf(" %c", &val);
                insert_value(liste[i], &val);
                break;
            }
            case FLOAT: {
                float val;
                printf("\nSaisissez le flotant souhaitez vous ajouter (float) : ");
                scanf("%f", &val);
                insert_value(liste[i], &val);
                break;
            }
            case DOUBLE: {
                double val;
                printf("\nSaisissez le double souhaitez vous ajouter (double) : ");
                scanf("%lf", &val);
                insert_value(liste[i], &val);
                break;
            }
            case STRING: {
                char val[100];
                printf("\nSaisissez le mot souhaitez vous ajouter (str) : ");
                scanf("%s", val);
                insert_value(liste[i], val);
                break;
            }

        }

    }
}

void add_col(COLUMN*** liste, int *taille){
    (*taille)++;
    *liste = realloc(*liste, (*taille)*sizeof (COLUMN*));
    ENUM_TYPE type;
    printf("Saisir le type de la colonne entre int(1), char(2), float(3), double(4), str(5): ");
    scanf("%d", &type);
    printf("\nSaisir le titre de la colonne :");
    char titre[100];
    scanf("%s", titre);
    (*liste)[*taille - 1] = create_column(type, titre);
    for (int i=0; i< (*liste)[0]->taille_log; i++){
        switch ((*liste)[*taille-1]->column_type) {
            case INT: {
                int val;
                printf("\nSaisissez l'entier que souhaitez vous ajouter a la ligne %d (int) : ",i);
                scanf(" %d", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case CHAR: {
                char val;
                printf("\nSaisissez le charactere que souhaitez vous ajouter a la ligne %d (char) : ", i);
                scanf(" %c", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case FLOAT: {
                float val;
                printf("\nSaisissez le flotant que souhaitez vous ajouter a la ligne %d (float) : ",i);
                scanf(" %f", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case DOUBLE: {
                double val;
                printf("\nSaisissez le double souhaitez que vous ajouter a la ligne %d (double) : ",i);
                scanf(" %lf", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case STRING: {
                char val[100];
                printf("\nSaisissez le mot que souhaitez vous ajouter a la ligne %d (str) : ", i);
                scanf(" %s", val);
                insert_value((*liste)[*taille], val);
                break;
            }

        }

    }
}

void suppr_ligne(COLUMN** liste, int taille) {
    printf("Saisissez la ligne que vous souhaitez supprimer : ");
    int ligne;
    scanf("%d", &ligne);
    if (ligne < 0 || ligne >= liste[0]->taille_log) {
        printf("Saisissez une ligne valide\n");
        return;
    }

    for (int i = 0; i < taille; i++) {
        COLUMN* col = liste[i];
        if (col->column_type == STRING) {
            free(col->data[ligne]->string_value);
        }
        free(col->data[ligne]);

        for (int j = ligne; j < col->taille_log - 1; j++) {
            col->data[j] = col->data[j + 1];
        }
        col->data[col->taille_log - 1] = NULL;
        col->taille_log--;
    }
}

void suppr_col(COLUMN*** liste, int *taille) {
    printf("Saisissez la colonne que vous souhaitez supprimer : ");
    int colonne;
    scanf("%d", &colonne);
    if (colonne < 0 || colonne >= *taille) {
        printf("Saisissez une colonne valide\n");
        return;
    }
    delete_column(&(*liste)[colonne]);

    for (int i = colonne; i < *taille - 1; i++) {
        (*liste)[i] = (*liste)[i + 1];
    }
    (*taille)--;
    if (*taille > 0) {
        *liste = realloc(*liste, (*taille) * sizeof(COLUMN*));
    } else {
        free(*liste);
        *liste = NULL;
    }
}

void renommer_col(COLUMN** liste, int taille){
    int col;
    printf("Saisisez la colonne que vous voulez renommer : ");
    scanf("%d", &col);
    if (col < 0 || col >= taille) {
        printf("Saisissez une colonne valide\n");
        return;
    }
    printf("\nVous voulez modifiez la colonne ayant comme titre %s", liste[col]->titre);
    printf("\nSaisissez le nouveau titre de la colonne : ");
    char titre[20];
    scanf("%19s", titre);

    char *nouveau_titre = calloc(strlen(titre) + 1, sizeof(char));
    strcpy(nouveau_titre, titre);
    free(liste[col]->titre);
    liste[col]->titre = nouveau_titre;

}

int rechercher_val(COLUMN** liste, int taille){
    int trouve = 0;
    ENUM_TYPE type;
    do{
    printf("Saisissez le type de la valeur que vous recherchez dans le CDataframe, 1 pour int...: ");
    scanf("%d", &type);} while (type<1 || type>5);
    switch (type) {
        case INT:{
            printf("\nSaissir la valeur recherche :");
            int val;
            scanf("%d", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == INT) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->int_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                        return 1;}
                    }
                }
            }
            break;}
        case CHAR:{
            printf("\nSaissir la valeur recherche :");
            char val;
            scanf(" %c", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == CHAR) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->char_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case FLOAT:{
            printf("\nSaissir la valeur recherche :");
            float val;
            scanf("%f", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == FLOAT) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if ( liste[i]->data[j]->float_value == val){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case DOUBLE:{
            printf("\nSaissir la valeur recherche :");
            double val;
            scanf("%lf", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == DOUBLE) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->double_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case STRING:{
            printf("\nSaisir la valeur recherchee :");
            char val[100];
            scanf("%s", val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == STRING) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (strcmp(val, liste[i]->data[j]->string_value) == 0){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
    }
    printf("\nLa valeur n a pas ete trouve dans le CDataframe");
    return 0;
}

void remplacer_valeur(COLUMN** liste, int taille){
    int ligne,col;
    printf("\nSaisir la ligne et la colonne sur lesquel se trouve la valeur que vous voulez remplacer [ligne,col]: ");
    scanf("%d,%d", &ligne,&col);

    if (col < 0 || col >= taille || ligne < 0 || ligne >= liste[col]->taille_log) {
        printf("Indices invalides.\n");
        return;
    }

    ENUM_TYPE type = liste[col]->column_type;


    switch (type) {
        case INT:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            int val;
            scanf("%d", &val);
            liste[col]->data[ligne]->int_value = val;
            break;}
        case CHAR:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            char val;
            scanf(" %c", &val);
            liste[col]->data[ligne]->char_value = val;
            break;}
        case FLOAT:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            float val;
            scanf("%f", &val);
            liste[col]->data[ligne]->float_value = val;
            break;}
        case DOUBLE:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            double val;
            scanf("%lf", &val);
            liste[col]->data[ligne]->double_value = val;
            break;}
        case STRING:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            char val[100];
            scanf("%s", val);
            free(liste[col]->data[ligne]->string_value);
            liste[col]->data[ligne]->string_value = malloc(strlen(val) + 1);
            strcpy(liste[col]->data[ligne]->string_value, val);
            break;}
    }

}

void affichage_par_index(COLUMN** liste, int taille){
    int colonne;
    do {
        printf("\nSaisir la colonne triee a partir de laquelle vous aller afficher le CDataframe :");
        scanf("%d", &colonne);
    } while (colonne<0||colonne>taille-1);
    char str[100];
    printf("Affichage du CDataframe :\n\n");

    for(int i=0; i<liste[0]->taille_log; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=0; j<taille; j++){
            COLUMN *col = liste[j];
            if (col->data[liste[colonne]->index[i]] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, liste[colonne]->index[i], str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}

void quicksort(COLUMN *col, int gauche, int droite) {
    if (gauche < droite){
        int pi = partition(col, gauche, droite);
        quicksort(col, gauche, pi-1);
        quicksort(col, pi + 1, droite);
    }
}


int partition(COLUMN *col, int gauche, int droite) {
    int i = gauche - 1;

    switch (col->column_type) {
        case INT: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->int_value <= pivot->int_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case CHAR: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->char_value <= pivot->char_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case FLOAT: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->float_value <= pivot->float_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case DOUBLE: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->double_value <= pivot->double_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case STRING: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || strcmp(col->data[col->index[j]]->string_value, pivot->string_value) <= 0)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        default:
            return -1;
    }
}

void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void tri_par_insertion(COLUMN *col) {
    printf("\ntri par insertion effectue\n");
    for (int i = 1; i < col->taille_log; i++) {
        int j = i;
        while (j > 0 && col->data[col->index[j - 1]] != NULL &&
               (col->data[col->index[j]] == NULL ||
                compare(col->data[col->index[j - 1]], col->data[col->index[j]], col->column_type) > 0)) {
            permuter(&(col->index[j]), &(col->index[j - 1]));
            j--;
        }
    }
}

int compare(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type) {
    switch (type) {
        case INT:
            return (a->int_value > b->int_value) - (a->int_value < b->int_value);
        case CHAR:
            return (a->char_value > b->char_value) - (a->char_value < b->char_value);
        case FLOAT:
            return (a->float_value > b->float_value) - (a->float_value < b->float_value);
        case DOUBLE:
            return (a->double_value > b->double_value) - (a->double_value < b->double_value);
        case STRING:
            return strcmp(a->string_value, b->string_value);
        default:
            return 0;
    }
}
