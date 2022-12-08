#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachet.c"

int main() {
    int numberOfDecks = 0;
    Deck **decks = (Deck **) malloc(0);
    char* buffer = (char*) malloc(50);

    fgets(buffer, 50, stdin);
    char* command = strtok(buffer, " \n");

    while (strstr(command, "EXIT") == 0) {
        if (strstr(command, "ADD_DECK")) {
            int numberOfCards = atoi(strtok(NULL, " \n"));
            numberOfDecks++;
            decks = (Deck **)realloc(decks, numberOfDecks * (sizeof(Deck *)));
            Deck* deck = createDeck();

            for (int i = 0; i < numberOfCards; i++) {
                fgets(buffer, 50, stdin);
                int n = atoi(strtok(buffer, " \n"));
                char s = createSymbol(strtok(NULL, " \n"));
                addCard(createCard(n, s), deck);
            }
            decks[numberOfDecks - 1] = deck;
            printf("The deck was successfully created with %d cards at %p.\n", numberOfCards, deck);
        }

        if (strstr(command, "DEL_DECK")) {
            int deckIndex = atoi(strtok(NULL, " \n"));
            if (deckIndex > numberOfDecks - 1)
                continue;
            Deck *deck = decks[deckIndex];
            printf("aaaaaaaaaaaaaaaaaaaa: %p\n", deck);
            deleteDeck(deck);
            free(deck);

            for (int i = deckIndex; i < numberOfDecks - 1; i++)
                decks[i] = decks[i + 1];
            
            numberOfDecks--;
            decks = realloc(decks, numberOfDecks);
            printf("The deck %d was successfully deleted.\n", deckIndex);
        }

        if (strstr(command, "DEL_CARD")) {
            int indexDeck = atoi(strtok(NULL, " \n"));
            int indexCard = atoi(strtok(NULL, " \n"));
            Deck *deck = decks[indexDeck];
            removeCard(deck, indexCard);
            if (deck->size == 0) {
                free(deck);
                printf("pachet gol -> sterg referinta din decks\n");
                for (int i = indexDeck; i < numberOfDecks - 1; i++)
                decks[i] = decks[i + 1];
                numberOfDecks--;
                decks = realloc(decks, numberOfDecks);
            }
                //shiftez la stanga vetorul
            printf("The card was successfully deleted from deck %d.\n", indexDeck);
        }

        if (strstr(command, "ADD_CARDS")) {
            int indexDeck = atoi(strtok(NULL, " \n"));
            int cardsNumber = atoi(strtok(NULL, " \n"));

            for (int i = 0; i < cardsNumber; i++) {
                fgets(buffer, 50, stdin);
                int n = atoi(strtok(buffer, " \n"));
                char symbol = createSymbol(strtok(NULL, " \n"));
                addCard(createCard(n, symbol), decks[indexDeck]);
            }

            printf("The cards were successfully added to deck %d.\n", indexDeck);
        }

        if (strstr(command, "DECK_NUMBER")) {
            printf("The number of decks is %d.\n", numberOfDecks);   
        }

        if (strstr(command, "DECK_LEN")) {
            int indexDeck = atoi(strtok(NULL, " \n"));
            printf("The length of deck %d is %d.\n", indexDeck, getSize(decks[indexDeck]));
        }

        if (strstr(command, "SHOW_ALL")) {
            for (int i = 0; i < numberOfDecks; i++) {
                printf("Deck %d:\n", i);
                printPachet(decks[i]);
            }
        }

 
        fgets(buffer, 50, stdin);
        command = strtok(buffer, " \n");
    }

    free(buffer);
    for (int i = 0; i < numberOfDecks; i++)
        free(decks[i]);
    free(decks);
    return 0;
}
