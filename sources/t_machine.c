#include <stdio.h>
#include <stdbool.h>
#include <mem.h>
#include "../headers/common.h"
#include "../headers/t_machine.h"

#define CMD_SHIFT 12

unsigned head_current_position;
char current_state[STATE_SIZE];
char tape[TAPE_SIZE];
char command_context[COMMAND_CONTEXT_SIZE];
_Bool is_debug_mode;
struct _iobuf *output_file;

static _Bool is_equals_current_value(const unsigned cmd_iterator) {
    const char current_symbol = tape[head_current_position];
    const char src_cmd_char = command_context[cmd_iterator];
    return current_symbol == src_cmd_char;
}

static _Bool is_equals_current_state(const unsigned cmd_iterator) {
    return command_context[cmd_iterator + 1] == ' '
           && command_context[cmd_iterator + 2] == current_state[0]
           && command_context[cmd_iterator + 3] == current_state[1]
           && command_context[cmd_iterator + 4] == ' ';
}

static void set_new_value_by(const unsigned cmd_iterator) {
    tape[head_current_position] = command_context[cmd_iterator + 5];
}

static void set_new_state_by(const unsigned cmd_iterator) {
    current_state[0] = command_context[cmd_iterator + 7];
    current_state[1] = command_context[cmd_iterator + 8];
}

static void modify_iterator_flag(const unsigned cmd_iterator, _Bool *is_simulating_ptr) {
    const char iterator_flag = command_context[cmd_iterator + 10];
    switch (iterator_flag) {
        case 'R':
            head_current_position++;
            break;
        case 'L':
            head_current_position--;
            break;
        case 'H':
            break;
        case 'S':
            *is_simulating_ptr = false;
            break;
        default:
            error("\nInvalid iterator flag\n");
    }
}

static void simulate() {
    const unsigned cmd_ctx_size = strlen(command_context);
    _Bool is_simulating = true;
    while (is_simulating) {
        unsigned cmd_iterator = 0;
        while (true) {
            if (cmd_iterator >= cmd_ctx_size) {
                error("\nCommand is not found\n");
            } else if (is_equals_current_value(cmd_iterator) && is_equals_current_state(cmd_iterator)) {
                break;
            } else {
                cmd_iterator += CMD_SHIFT;
            }
        }
        set_new_value_by(cmd_iterator);
        set_new_state_by(cmd_iterator);
        modify_iterator_flag(cmd_iterator, &is_simulating);
    }
}

void start_t_machine(
        const char *command_file_path,
        const char *input_file_path,
        const char *output_file_path
) {
    //Read commands
    read_file(command_context, command_file_path);
    //Read tape
    read_file(tape, input_file_path);
    //Open output file
    output_file = fopen(output_file_path, WRITE_MODE);
    //Make simulating
    simulate();
    //Close output file
    fclose(output_file);
}