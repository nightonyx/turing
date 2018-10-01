#ifndef TURING_COMMON_H
#define TURING_COMMON_H

char *substring(const char *source, unsigned start, unsigned end);

_Bool matches_state(const char *state);

void error(const char *message);

#endif //TURING_COMMON_H