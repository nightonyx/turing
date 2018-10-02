#ifndef TURING_COMMON_H
#define TURING_COMMON_H

#define READ_MODE "r"

#define WRITE_MODE "w"

_Bool matches_state(const char *state);

void error(const char *message);

void read_file(char *dest, unsigned capacity, const char *path);

#endif //TURING_COMMON_H