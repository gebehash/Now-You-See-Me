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
    if (pachet == NULL)
        return;
    
    while (pachet->size) {
        removeCard(pachet, 0);
        if (pachet == NULL)
            return;
    }
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
    
    pachet->head = mid->next;
    pachet->tail = mid;
    mid->next = 0;
    last->next = first;
}

Deck* mergeDecks(Deck* deck1, Deck* deck2) {
    printf("\n");
    printPachet(deck1);
        printf("\n");

    printPachet(deck2);
    Node* head1 = deck1->head;
    Node* head2 = deck2->head;
    Deck* newDeck = createDeck();
    
    while (head1 && head2) {
        Node* aux1 = head1;
        Node *aux2 = head2;
        addCard(head1, newDeck);
        addCard(head2, newDeck);
        head1 = head1->next;
        head2 = head2->next;
        aux1->next = NULL;
        aux2->next = NULL;
        printf("%p\t%p\n", head1, head2);
    }

    while (head1) {
        Node* aux1 = head1;
        addCard(head1, newDeck);
        head1 = head1->next;
        if (head1->next == 0)
            head1 = 0;
        aux1->next = NULL;
        printf("%p\t%p\n", head1, head2);
        printf("Current card: %p, -> next: %p\n", head1, head1->next);
        for (long long i = 0; i < __INT_MAX__/ 1000;) {
            i++;
        }
    }

    while (head2) {
        Node *aux2 = head2;
        addCard(head2, newDeck);
        head2 = head2->next;
        aux2->next = NULL;
                printf("%p\t%p\n", head1, head2);

    }
    return newDeck;
}