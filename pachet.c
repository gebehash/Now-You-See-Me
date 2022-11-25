#include "carte.c"
#pragma pack(1)
typedef struct Pachet {
    Node* head;
    Node* tail;
    int size;
}Pachet;


Pachet* createPachet() {
    Pachet* p = malloc(sizeof(Pachet));
    p->head = 0;
    p->tail = 0;
    p->size = 0;
    // printf("%d", sizeof(Pachet));
    return p;
}

int getSize(Pachet* p) {
    return p->size;
}

void addCard(/*int val, char simbol*/Node* node, Pachet* pachet) {
    // Node *node = createCard(val,simbol);

    if (pachet->head != 0) {
        pachet->tail->next = node;
        node->prev = pachet->tail;
        pachet->tail = node;
    } else {
        pachet->head = node;
        pachet->tail = node;
    }
    //printf("Added card %d\n", val);
    pachet->size++;
    // printf("pachetsize  %d\n", pachet->size);
}

void removeCard(Pachet* pachet, int index) {
    if (pachet->size == 0) {
        free(pachet);
        return;
    }
    if (pachet->size <= index)
        return;
    if (index == 0) {
        Node *aux = pachet->head;
        if (pachet->size == 1) {
            pachet->tail = 0;
            pachet->head = 0;
        } else {
            pachet->head = pachet->head->next;
            pachet->head->prev = 0;
        }
        free(aux);
    } else
        removeCardAtPos(pachet->head, index);
    pachet->size--;
}

void deletePachet(Pachet* pachet) {
    while (pachet->size)
        removeCard(pachet, 0);
    //free(pachet);
}

void printPachetReal(Node* head) {
    if (head == 0)
        return;
    printCard(head);
    // printf("\t");
    printPachetReal(head->next);
}

void printPachet(Pachet* pachet) {
    if (pachet == NULL)
        return;
    if (pachet->size == 0)
        printf("Pachet gol\n");
    else
        printPachetReal(pachet->head); 
}
