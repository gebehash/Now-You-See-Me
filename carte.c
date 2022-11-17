typedef struct Node {
    struct Node* prev;
    struct Node* next;
    short val;
    char simbol;
}Node;

Node* createCard(short val, char simbol) {
    Node* node = malloc(sizeof(Node));
    node->prev = 0;
    node->next = 0;
    node->val = val;
    node->simbol = simbol;
    //printf("Node %d: %p\n", node->val, node);
    return node;
}

void deleteCard(Node* node) {
    //printf("deleted %d: %p\n", node->val, node);
    if (node->prev != NULL && node->next != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else {
        printf("Error: deleteCard\n");
    }
    free(node);
}

void removeCardAtPos(Node* node, int index) {
    if (index == 0)
        deleteCard(node);
    else
        removeCardAtPos(node->next, index - 1);
}

void printCard(Node* node) {
    printf("%d%c", node->val, node->simbol);
}