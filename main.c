#include <stdio.h>
#include "projet.h"

int main() {
    COLUMN* ptr = create_column("colonne_1");
    insert_value(ptr, 7);

    insert_value(ptr, 73);
    insert_value(ptr, 103);
    insert_value(ptr, 27);
    insert_value(ptr, 27);
    insert_value(ptr, 27);
    insert_value(ptr, 26);
    insert_value(ptr, 0);
    insert_value(ptr, 5);
    print_col(ptr);

    printf("%d\n", nb_occ(ptr, 122));
    printf("%d\n", position(ptr, 100));
    printf("%d\n", superieur(ptr, 4));



    delete_column(&ptr);

    return 0;
}
