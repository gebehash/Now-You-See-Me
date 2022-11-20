#include "carte.c"

typedef struct Pachet {
    Node* head;
    Node* tail;
    short size;
}Pachet;

Pachet* createPachet() {
    Pachet* p = malloc(sizeof(Pachet));
    p->head = 0;
    p->tail = 0;
    p->size = 0;
    return p;
}

void addCard(/*short val, char simbol*/Node* node, Pachet* pachet) {
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
}

void removeCard(Pachet* pachet, int index) {
    //printf("Removing card %d\n", pachet->head->val);
    if (pachet->size == 0 || pachet->size <= index)
        return;
    if (index == 0) {
        Node *aux = pachet->head;
        if (pachet->size == 1) {
            pachet->tail = 0;
            pachet->head = 0;
        } else{
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
    free(pachet);
}

void printPachetReal(Node* head) {
    if (head == 0)
        return;
    printCard(head);
    printf("\t");
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
