#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include <stdio.h>
#include <process.h>

char *substring(const char *source, const unsigned start, const unsigned end) {
    const unsigned dest_size = end - start + 1;
    char *dest = calloc(dest_size, sizeof(char));
    for (unsigned i = 0; i < dest_size; ++i) {
        dest[i] = source[start + i];
    }
    return dest;
}

_Bool matches_state(const char *state) {
    return strlen(state) == 2
           && isalpha(state[0])
           && isdigit(state[1]);
}

void error(const char *message) {
    perror(message);
    exit(1);
}