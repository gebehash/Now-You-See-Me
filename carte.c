typedef struct Node {
    struct Node* prev;
    struct Node* next;
    short val;
    char simbol;
}Node;

Node* createNode(short val, char simbol) {
    Node* node = malloc(sizeof(Node));
    node->prev = 0;
    node->next = 0;
    node->val = val;
    node->simbol = simbol;
 
    return node;
}

void deleteCard(Node* node) {
    printf("%d", node->val);
    if (node->prev != NULL && node->next != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    if (node->prev != NULL && node->next == NULL)
        node->prev->next = 0;
        
    //if (node->prev == NULL && node->next != NULL)
        

    free(node);
}

void removeCardAtPos(Node* node, int index) {
    if (index == 0) {
        deleteCard(node);
    } else {
        removeCardAtPos(node->next, index - 1);
    }
}

void printCard(Node* node) {
    printf("%d : %c", node->val, node->simbol);
}