#include "carte.c"
#pragma pack(1)
typedef struct Deck {
    Node* head;
    Node* tail;
    int size;
}Deck;

Deck* createDeck() {
    Deck* p = malloc(sizeof(Deck));
    p->head = 0;
    p->tail = 0;
    p->size = 0;
    // printf("%d", sizeof(Deck));
    return p;
}

int getSize(Deck* p) {
    return p->size;
}

void addCard(/*int val, char simbol*/Node* node, Deck* pachet) {
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

void removeCard(Deck* pachet, int index) {
    if (pachet->size == 0)
        return;
    if (pachet->size <= index)
        return;
    if (index == 0) {
        Node *aux = pachet->head;
        if (pachet->size == 1) {
            deleteCard(pachet->head);
        } else {
            pachet->head = pachet->head->next;
            pachet->head->prev = 0;
            free(aux);
        }
    } else
        removeCardAtPos(pachet->head, index);
    pachet->size--;
}

void deleteDeck(Deck* pachet) {
    printf("deck: %p", pachet);
    if (pachet == NULL)
        return;
    
    while (pachet->size) {
        removeCard(pachet, 0);
        if (pachet == NULL)
            return;
    }
}

void printPachetReal(Node* head) {
    if (head == NULL)
        return;
    printCard(head);
    printPachetReal(head->next);
}

void printPachet(Deck* pachet) {
    if (pachet == NULL)
        return;
    if (pachet->size == 0)
        printf("Deck gol\n");
    else
        printPachetReal(pachet->head); 
}
