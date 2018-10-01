#ifndef TURING_COMMON_H
#define TURING_COMMON_H

#define READ_MODE "r"

#define WRITE_MODE "w"

char *substring(const char *source, unsigned start, unsigned end);

_Bool matches_state(const char *state);

void error(const char *message);

void read_file(char *dest, const char *path);

#endif //TURING_COMMON_H