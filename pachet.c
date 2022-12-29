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
    pachet->size++;
}

void removeCard(Deck* pachet, int index) {
    if (pachet->size == 0)
        return;
    if (pachet->size <= index)
        return;
    if (index == 0) {
        Node *aux = pachet->head;
        pachet->head = pachet->head->next;
        deleteCard(aux);
        if (pachet->size == 1)
            pachet->tail = 0;
    } else {
        removeCardAtPos(pachet->head, index);
        Node *head = pachet -> head;
        while (head->next)
            head = head->next;
        pachet->tail = head;
    }
    pachet->size = pachet->size - 1;
}

void deleteDeck(Deck* pachet) {
    if (pachet == NULL)
        return;
    
    while (pachet->size)
        removeCard(pachet, 0);
    free(pachet);
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
    if (pachet->size == 0);
        //printf("Deck gol\n");
    else
        printPachetReal(pachet->head); 
}

void shuffleDeck(Deck* pachet) {
    Node* first = pachet->head;
    Node* last = pachet->tail;
    Node* mid = pachet->head;
    
    for (int i = 0; i < pachet->size/2; i++)
        mid = mid->next;
    
    pachet->head = mid;
    pachet->tail = mid->prev;
    mid->prev = 0;
    last->next = first;
    first->prev = mid;
    first->next = 0;
}

Deck* mergeDecks(Deck* deck1, Deck* deck2) {
    Node* head1 = deck1->head;
    Node* head2 = deck2->head;
    Deck* newDeck = createDeck();
    
    while (head1 && head2) {
        Node *aux1 = createCard(head1->val, head1->simbol);
        Node *aux2 = createCard(head2->val, head2->simbol);
        addCard(aux1, newDeck);
        addCard(aux2, newDeck);
        head1 = head1->next;
        head2 = head2->next;
    }

    while (head1) {
        Node *aux1 = createCard(head1->val, head1->simbol);
        addCard(aux1, newDeck);
        head1 = head1->next;
    }

    while (head2) {
        Node *aux2 = createCard(head1->val, head1->simbol);
        addCard(aux2, newDeck);
        head2 = head2->next;
    }
    return newDeck;
}

void reverseDeck(Deck *deck) {
    Node* aux = deck->head;
    deck->head = deck->tail;
    deck->tail = aux;

    Node* head = deck->head;

    while(head != 0) {
        aux = head;
        head = head->prev;
        aux->prev = aux->next;
        aux->next = head;
    }
}