#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachet.c"

int main() {
    void *vector = malloc(1);
    int total_size = 0;
    int index = 0;

    char* buffer = (char*) malloc(50);
    fgets(buffer, 50, stdin);

    while (strstr(buffer, "EXIT") == 0) {
        char* command = strtok(buffer, " \n");

        if (strstr(command, "ADD_DECK") == 0) {
            int number = atoi(strtok(NULL, " \n"));
            total_size += 8;
            vector = realloc(vector, total_size);
            Pachet* p = createPachet();

            for (int i = 0; i < number; i++) {
                addCard(createCard(strtok(NULL, " \n")))
            }
            
            
            
            memcpy(vector + (index * 8), p, 8);
        }
    }


    free(buffer);
    return 0;
}
