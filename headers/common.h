#ifndef TURING_COMMON_H
#define TURING_COMMON_H

#define READ_MODE "r"

#define WRITE_MODE "w"

typedef struct str {
    char *data;
    unsigned capacity;
} str;

str *create_str();

void grow_str(str *string);

_Bool matches_state(const char *state);

void error(const char *message);

void read_file(struct str *dest, const char *path);

#endif //TURING_COMMON_H