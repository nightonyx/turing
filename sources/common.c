#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include <stdio.h>
#include <process.h>
#include <stdbool.h>
#include "../headers/common.h"

_Bool matches_state(const char *state) {
    return strlen(state) == 2
           && isalpha(state[0])
           && isdigit(state[1]);
}

void error(const char *message) {
    perror(message);
    exit(1);
}

void read_file(char *dest, const unsigned capacity, const char *path) {
    FILE *file = fopen(path, READ_MODE);
    if (file) {
        const unsigned size = capacity;
        unsigned position = 0;
        while (true) {
            const char ch = (const char) fgetc(file);
            if (ch == EOF || position >= size) {
                break;
            } else {
                dest[position++] = ch;
            }
        }
        fclose(file);
    } else {
        error("\nCan not get access to the file\n");
    }
}