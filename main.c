#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachet.c"
#define SIZEOF_PACHET 8

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
}

int main() {
    void *vector = malloc(1);
    int total_size = 0;
    int index = 0;

    char* buffer = (char*) malloc(50);
    
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

        fgets(buffer, 50, stdin);
        command = strtok(buffer, " \n");
    }

    for (int i = 0; i < 2; i++) {
        printPachet(vector + i * SIZEOF_PACHET);
        printf("\n");
    }


    free(buffer);
    return 0;
}
