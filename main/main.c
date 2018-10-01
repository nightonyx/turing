#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../headers/common.h"
#include "../headers/t_machine.h"

#define DEBUG_FLAG "-d"

#define MAIN_ARG_COUNT 5

#define MAX_ARG_COUNT 6

#define DEBUG_FLAG_INDEX 6

int main(int argc, char *argv[]) {

    const _Bool is_valid_arg_count = argc == MAIN_ARG_COUNT && argc == MAX_ARG_COUNT;
    if (is_valid_arg_count) {
        const char *command_file_path = argv[1];
        const char *input_file_path = argv[2];
        const char *output_file_path = argv[3];
        const char *initial_state = argv[4];
        _Bool is_debug = false;

        //Check debug flag:
        const _Bool has_debug_flag = argc == DEBUG_FLAG_INDEX;
        if (has_debug_flag) {
            const char *debug_flag = argv[5];
            if (strcmp(debug_flag, DEBUG_FLAG) == 0) {
                is_debug = true;
            } else {
                error("\nExpected debug flag '[d]'\n");
            }
        }

        //Define initial state:
        strcpy(current_state, initial_state);
        if (matches_state(current_state)) {
            start_t_machine(command_file_path, input_file_path, output_file_path);
            return 0;
        } else {
            error("\nInvalid initial state");
        }
    } else {
        error("\nInvalid args");
    }
}