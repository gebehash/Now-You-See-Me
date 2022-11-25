#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachet.c"

int main() {
    int total_size = 0;
    void *vector = malloc(total_size);
    int index = 0;
    int SIZEOF_PACHET = sizeof(Pachet);

    char* buffer = (char*) malloc(50);
    //printf("%d", sizeof(void*));

    fgets(buffer, 50, stdin);
    char* command = strtok(buffer, " \n");

    while (strstr(command, "EXIT") == 0) {
        if (strstr(command, "ADD_DECK")) {
            int number = atoi(strtok(NULL, " \n"));
            total_size += SIZEOF_PACHET;
            vector = realloc(vector, total_size);
            Pachet* p = createPachet();

            for (int i = 0; i < number; i++) {
                fgets(buffer, 50, stdin);
                int n = atoi(strtok(buffer, " \n"));
                char s = getSymbol(strtok(NULL, " \n"));
                addCard(createCard(n, s), p);
            }
            
            memcpy(vector + (index * SIZEOF_PACHET), p, SIZEOF_PACHET);
            index ++;

            printf("The deck was successfully created with %d cards.\n", number);
        }

        if (strstr(command, "DEL_DECK")) {
            int number = atoi(strtok(NULL, " \n"));
            deletePachet(vector + number * SIZEOF_PACHET);
            total_size -= SIZEOF_PACHET;
            memcpy(vector + (number * SIZEOF_PACHET), vector + ((number + 1)* SIZEOF_PACHET), (total_size) - (SIZEOF_PACHET * number));
            vector = realloc(vector, total_size);

            printf("The deck %d was successfully deleted.\n", number);
        }

        if (strstr(command, "DEL_CARD")) {
            int index_deck = atoi(strtok(NULL, " \n"));
            int index_card = atoi(strtok(NULL, " \n"));
            removeCard(vector + (index_deck * SIZEOF_PACHET), index_card);

            printf("The card was successfully deleted from deck %d.\n", index_deck);
        }

        if (strstr(command, "ADD_CARDS")) {
            int index_deck = atoi(strtok(NULL, " \n"));
            int number = atoi(strtok(NULL, " \n"));

            for (int i = 0; i < number; i++) {
                fgets(buffer, 50, stdin);
                int n = atoi(strtok(buffer, " \n"));
                char s = getSymbol(strtok(NULL, " \n"));
                addCard(createCard(n, s), vector + (index_deck * SIZEOF_PACHET));
            }

            printf("The cards were successfully added to deck %d.\n", index_deck);
        }

        if (strstr(command, "DECK_NUMBER")) {
            printf("The number of decks is %d.\n", total_size / SIZEOF_PACHET);   
        }

        if (strstr(command, "DECK_LEN")) {
            int index_deck = atoi(strtok(NULL, " \n"));
            printf("The length of deck %d is %d.\n", index_deck, getSize(vector + index_deck * SIZEOF_PACHET));
        }

        if (strstr(command, "SHOW_ALL")) {
            for (int i = 0; i < total_size / SIZEOF_PACHET; i++) {
                printf("Deck %d:\n", i);
                printPachet(vector + i * SIZEOF_PACHET);
                printf("\n");
            }
        }

 
        fgets(buffer, 50, stdin);
        command = strtok(buffer, " \n");
    }

    // for (int i = 0; i < 2; i++) {
    //     printPachet(vector + i * SIZEOF_PACHET);
    //     printf("\n");
    // }
    printf("VECTOR: %p\n", vector);
    printf("_____sizeof_pp::%d\n", total_size / SIZEOF_PACHET);
    // for (int i = 0; i < total_size / SIZEOF_PACHET; i++) {
    //     printf("\tdeleted at: %p\n", vector + i * SIZEOF_PACHET);
    //     deletePachet(vector + i * SIZEOF_PACHET);
    //     free()
    // }

    free(buffer);
    free(vector);
    return 0;
}
