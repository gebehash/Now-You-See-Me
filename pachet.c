#include "carte.c"

typedef struct Pachet {
    Node* head;
    Node* tail;
    short size;
}Pachet;

void addCard(short val, char simbol, Pachet* pachet) {
    Node *node = createNode(val,simbol);

    if (pachet->head != 0) {
        pachet->tail->next = node;
        node->prev = pachet->tail;
        pachet->tail = node;
    } else {
        pachet->head = node;
        pachet->tail = node;
    }
}

void removeCard(Pachet* pachet, int index) {
    removeCardAtPos(pachet->head, index);
}

void printPachetReal(Node* head) {
    if (head == 0)
        return;

    printCard(head);
    printf("\n");

    printPachetReal(head->next);
}

void printPachet(Pachet* pachet) {
    if (pachet == NULL)
        return;

    printPachetReal(pachet->head); 
}
