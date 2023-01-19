#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachet.c"
#include <unistd.h>

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

#define EXIT 0
#define ADD_DECK 1
#define DEL_DECK 2
#define DEL_CARD 3
#define ADD_CARDS 4
#define DECK_NUMBER 5
#define DECK_LEN 6
#define SHUFFLE_DECK 7
#define MERGE_DECKS 8
#define SPLIT_DECK 9
#define REVERSE_DECK 10
#define SHOW_DECK 11
#define SHOW_ALL 12

int getCommand(char *command) {
    if (strstr(command, "EXIT"))
        return EXIT;
    if (strstr(command, "ADD_DECK"))
        return ADD_DECK;
    if (strstr(command, "DEL_DECK"))
        return DEL_DECK;
    if (strstr(command, "DEL_CARD"))
        return DEL_CARD;
    if (strstr(command, "ADD_CARDS"))
        return ADD_CARDS;
    if (strstr(command, "DECK_NUMBER"))
        return DECK_NUMBER;
    if (strstr(command, "DECK_LEN"))
        return DECK_LEN;
    if (strstr(command, "SHUFFLE_DECK"))
        return SHUFFLE_DECK;
    if (strstr(command, "MERGE_DECKS"))
        return MERGE_DECKS;
    if (strstr(command, "SPLIT_DECK"))
        return SPLIT_DECK;
    if (strstr(command, "REVERSE_DECK"))
        return REVERSE_DECK;
    if (strstr(command, "SHOW_DECK"))
        return SHOW_DECK;
    if (strstr(command, "SHOW_ALL"))
        return SHOW_ALL;
    return -1;
}

int main() {
    int numberOfDecks = 0;
    Deck **decks = (Deck **) malloc(0);
    char* buffer = (char*) malloc(50);

    fgets(buffer, 50, stdin);
    char* command = strtok(buffer, " \n");
    
    while (getCommand(command)) {
        switch (getCommand(command)) {
            case ADD_DECK : {
                int numberOfCards = atoi(strtok(NULL, " \n"));
                numberOfDecks++;
                decks = (Deck **)realloc(decks, numberOfDecks * (sizeof(Deck *)));
                Deck* deck = createDeck();

                for (int i = 0; i < numberOfCards; i++) {
                    fgets(buffer, 50, stdin);
                    int n = atoi(strtok(buffer, " \n"));
                    char s = createSymbol(strtok(NULL, " \n"));
                    if (!(n>=1 && n<=14) || !(strstr(getSymbol(s),"HEART") || strstr(getSymbol(s), "SPADE") || strstr(getSymbol(s), "CLUB") || strstr(getSymbol(s), "DIAMOND"))) {
                        printf("The provided card is not a valid one.\n");
                        i--;
                    } else addCard(createCard(n, s), deck);
                }
                decks[numberOfDecks - 1] = deck;
                printf("The deck was successfully created with %d cards.\n", numberOfCards);
            }   break;

            case DEL_DECK : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else if (!(deckIndex > numberOfDecks - 1)) {
                    Deck *deck = decks[deckIndex];
                    //printf("aaaaaaaaaaaaaaaaaaaa: %p\n", deck);
                    deleteDeck(deck);
                    for (int i = deckIndex; i < numberOfDecks - 1; i++)
                        decks[i] = decks[i + 1];
                    
                    numberOfDecks--;
                    decks = realloc(decks, numberOfDecks * (sizeof(Deck *)));
                    printf("The deck %d was successfully deleted.\n", deckIndex);
                }
            }   break;

            case DEL_CARD : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                int indexCard = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    Deck *deck = decks[deckIndex];
                    if (indexCard < 0 || indexCard >= deck->size)
                        printf("The provided index is out of bounds for deck %d.\n", deckIndex);
                    else {
                        removeCard(deck, indexCard);
                        if (deck->size == 0) {
                            free(deck);
                            //printf("pachet gol -> sterg referinta din decks\n");
                            for (int i = deckIndex; i < numberOfDecks - 1; i++)
                            decks[i] = decks[i + 1];
                            numberOfDecks--;
                            decks = realloc(decks, numberOfDecks * (sizeof(Deck *)));
                        }
                            //shiftez la stanga vetorul
                        printf("The card was successfully deleted from deck %d.\n", deckIndex);
                    }
                }
            }   break;

            case ADD_CARDS : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    int cardsNumber = atoi(strtok(NULL, " \n"));
                    for (int i = 0; i < cardsNumber; i++) {
                        fgets(buffer, 50, stdin);
                        int n = atoi(strtok(buffer, " \n"));
                        char s = createSymbol(strtok(NULL, " \n"));
                        if (!(n>=1 && n<=14) || !(strstr(getSymbol(s),"HEART") || strstr(getSymbol(s), "SPADE") || strstr(getSymbol(s), "CLUB") || strstr(getSymbol(s), "DIAMOND"))) {
                            printf("The provided card is not a valid one.\n");
                            i--;
                        } else addCard(createCard(n, s), decks[deckIndex]);
                    }
                    printf("The cards were successfully added to deck %d.\n", deckIndex);
                }
            }   break;

            case DECK_NUMBER : {
                printf("The number of decks is %d.\n", numberOfDecks);   
            }   break;

            case DECK_LEN : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else
                    printf("The length of deck %d is %d.\n", deckIndex, getSize(decks[deckIndex]));
            }   break;

            case SHOW_ALL : {
                // printf("NUMBER of Decks: %d\n", numberOfDecks);
                for (int i = 0; i < numberOfDecks; i++) {
                    printf("Deck %d:\n", i);
                    printPachet(decks[i]);
                }
            }   break;

            case SHUFFLE_DECK : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    Deck *deck = decks[deckIndex];
                    shuffleDeck(deck);
                }
            }   break;

            case MERGE_DECKS: {
                int deckIndex1 = atoi(strtok(NULL, " \n"));
                int deckIndex2 = atoi(strtok(NULL, " \n"));
                if ((deckIndex1 < 0 || deckIndex1 >= numberOfDecks) || (deckIndex2 < 0 || deckIndex2 >= numberOfDecks))
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    Deck *deck1 = decks[deckIndex1];
                    Deck *deck2 = decks[deckIndex2];
                    Deck *newDeck = mergeDecks(deck1, deck2);
                    //printf("Merge completed successfully!\n");
                    deleteDeck(deck1);
                    deleteDeck(deck2);
                    if (deckIndex1 > deckIndex2)
                        swap(&deckIndex1, &deckIndex2);
                    for (int i = deckIndex1; i < numberOfDecks - 1; i++)
                        decks[i] = decks[i + 1];
                    numberOfDecks--;
                    deckIndex2--;
                    for (int i = deckIndex2; i < numberOfDecks - 1; i++)
                        decks[i] = decks[i + 1];
                    decks = (Deck **)realloc(decks, numberOfDecks * (sizeof(Deck *)));
                    decks[numberOfDecks - 1] = newDeck;
                    printf("The deck %d and the deck %d were successfully merged.\n", deckIndex1, deckIndex2);
                }
            }   break;

            case SPLIT_DECK: {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    int splitIndex = atoi(strtok(NULL, " \n"));
                    if (splitIndex != 0 && (splitIndex != (decks[deckIndex]->size) - 1)) {
                        Deck *deck1 = createDeck();
                        Deck *deck2 = createDeck();

                        numberOfDecks++;
                        decks = realloc(decks, numberOfDecks * (sizeof(Deck *)));

                        Node *node = decks[deckIndex]->head;
                        for (int i = 0; i < splitIndex; i++) {
                            addCard(createCard(node->val, node->simbol), deck1);
                            node = node->next;
                        }
                        while (node != 0) {
                            addCard(createCard(node->val, node->simbol), deck2);
                            node = node->next;
                        }
                        deleteDeck(decks[deckIndex]);
                        decks[deckIndex] = deck1;
                        for (int i = numberOfDecks - 1; i > deckIndex; i--)
                            decks[i] = decks[i-1];
                        decks[deckIndex+1] = deck2;
                    }
                    printf("The deck %d was successfully split by index %d.\n", deckIndex, splitIndex);  
                }
            }   break;

            case REVERSE_DECK: {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    reverseDeck(decks[deckIndex]);
                    printf("The deck %d was successfully reversed.\n", deckIndex);
                }
            }   break;

            case SHOW_DECK : {
                int deckIndex = atoi(strtok(NULL, " \n"));
                if (deckIndex < 0 || deckIndex >= numberOfDecks)
                    printf("The provided index is out of bounds for the deck list.\n");
                else {
                    printf("Deck %d:\n", deckIndex);
                    printPachet(decks[deckIndex]);
                }
            }   break;
                
            default :
                printf("Invalid command. Please try again.\n");
        }

        // printf("deck 0 size: %d\n", decks[0]->size);
        // printf("%d => ", decks[0]->head->val);
        // Node *head = decks[0]->head;
        // while (head) {
        //     printf("%d%s | ", head->val, getSymbol(head->simbol));
        //     head = head -> next;
        // }
        // printf(" <= %d\n", decks[0]->tail->val);
        // printf("%d => ", decks[0]->tail->val);
        // head = decks[0]->tail;
        // while (head) {
        //     printf("%d%s | ", head->val, getSymbol(head->simbol));
        //     head = head -> prev;
        // }
        // printf(" <= %d\n", decks[0]->head->val);
        // printf("\n");

        fgets(buffer, 50, stdin);
        command = strtok(buffer, " \n");
    }

    free(buffer);
    for (int j = 0; j < numberOfDecks; j++)
        deleteDeck(decks[j]);
    free(decks);
    return 0;
}
