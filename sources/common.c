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

str *create_str(){
    str *string = calloc(1, sizeof(str));
    string->capacity = 2;
    string->data = calloc(2, sizeof(char));
    return string;
}

void grow_str(str *dest) {
    const unsigned old_capacity = dest->capacity;
    dest->capacity = old_capacity * 2;
    char *old_data = dest->data;
    dest->data = calloc(dest->capacity, sizeof(char));
    strcpy(dest->data, old_data);
    for (unsigned i = old_capacity - 1; i < dest->capacity - 1; ++i) {
        dest->data[i] = ' ';
    }
    printf("\nWAS GROWWW\n!");
    free(old_data);
}

void read_file(str *dest, const char *path) {
    FILE *file = fopen(path, READ_MODE);
    if (file) {
        unsigned position = 0;
        while (true) {
            const char ch = (const char) fgetc(file);
            if (ch == EOF) {
                break;
            } else {
                if (position >= dest->capacity - 1) {
                    grow_str(dest);
                }
                dest->data[position++] = ch;
                printf("\nSSS:%s\n", dest->data);
            }
        }
        fclose(file);
    } else {
        error("\nCan not get access to the file\n");
    }
}