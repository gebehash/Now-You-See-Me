#include <stdio.h>
#include <stdlib.h>
#include "pachet.c"

int main() {
    Pachet* p1 = malloc(sizeof(Pachet));
    addCard(5, 'h', p1);
    // printCard(p1->head);
    // printf("\n");
    // printCard(p1->tail);
    // printf("\n");
    addCard(7, 'c', p1);
    // printCard(p1->tail);
    // printf("\n");
    addCard(2, 'd', p1);
    removeCard(p1, 0);
    removeCard(p1, 0);
    removeCard(p1, 0);

    printPachet(p1);




    return 0;
}
