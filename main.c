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
        char* command = strtok(buffer, " ");

        if (strstr(command, "ADD_DECK") == 0) {
            int number = atoi(strtok(NULL, " "));
            total_size += 8;
            vector = realloc(vector, total_size);
            vector[index * 8] = 0;
        }
    }


    free(buffer);
    return 0;
}
