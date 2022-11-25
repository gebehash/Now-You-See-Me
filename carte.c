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
    //printf("Node %d: %p\n", node->val, node);
    return node;
}

char getSymbol(char* string) {
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

char* getSymbol2(char c) {
    if (c == 'h') {
        return "HEART";
    } else if (c =='c') {
        return "CLUB";
    } else if (c == 'd') {
        return "DIAMOND";
    } else if (c=='s') {
        return "SPADE";
    }
    return NULL;
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
    printf("\t%d %s\n", node->val, getSymbol2(node->simbol));
}