typedef struct Node {
    struct Node* prev;
    struct Node* next;
    int val;
    char simbol;
}Node;

Node* createCard(int val, char simbol) {
    Node* node = malloc(sizeof(Node));
    node->prev = 0;
    node->next = 0;
    node->val = val;
    node->simbol = simbol;
    //printf("Created card %d at %p\n", node->val, node);
    return node;
}

char createSymbol(char* string) {
    if (strstr(string, "HEART")) {
        return 'h';
    } else if (strstr(string, "CLUB")) {
        return 'c';
    } else if (strstr(string, "DIAMOND")) {
        return 'd';
    } else if (strstr(string, "SPADE")) {
        return 's';
    }
    return 0;
}

char* getSymbol(char c) {
    if (c == 'h') {
        return "HEART";
    } else if (c =='c') {
        return "CLUB";
    } else if (c == 'd') {
        return "DIAMOND";
    } else if (c=='s') {
        return "SPADE";
    }
    return "";
}

void deleteCard(Node* node) {
    if (node == NULL)
        return;
    //printf("deleted %d: %p\n", node->val, node);
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    
    //printf("free card at: %p\n", node);
    free(node);
}

void removeCardAtPos(Node* node, int index) {
    if (index == 0)
        deleteCard(node);
    else
        removeCardAtPos(node->next, index - 1);
}

void printCard(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("\t%d %s\n", node->val, getSymbol(node->simbol));
}
