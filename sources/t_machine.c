#include <stdio.h>
#include <stdbool.h>
#include <mem.h>
#include <malloc.h>
#include "../headers/common.h"
#include "../headers/t_machine.h"

#define COMMAND_SHIFT 12

#define USER_MESSAGE_MAX_SIZE 3

#define LINE_BREAK_SIZE 1

unsigned head_current_position;
char current_state[STATE_SIZE];
str *tape;
str *command_context;
_Bool is_debug_mode;
struct _iobuf *output_file;

static _Bool is_equals_current_value(const unsigned command_iterator) {
    const char current_symbol = tape->data[head_current_position];
    const char src_cmd_char = command_context->data[command_iterator];
    printf("\n%c curr_v:\n", current_symbol);
    printf("\n%c cmd_v:\n", src_cmd_char);
    return current_symbol == src_cmd_char;
}

static _Bool is_equals_current_state(const unsigned command_iterator) {
    const char *data = command_context->data;
    return data[command_iterator + 1] == ' '
           && data[command_iterator + 2] == current_state[0]
           && data[command_iterator + 3] == current_state[1]
           && data[command_iterator + 4] == ' ';
}

static void set_new_value(const unsigned command_iterator) {
    tape->data[head_current_position] = command_context->data[command_iterator + 5];
}

static void set_new_state(const unsigned command_iterator) {
    char *data = command_context->data;
    current_state[0] = data[command_iterator + 7];
    current_state[1] = data[command_iterator + 8];
}

static void modify_iterator_flag(const unsigned command_iterator, _Bool *is_simulating_pointer) {
    const char iterator_flag = command_context->data[command_iterator + 10];
    switch (iterator_flag) {
        case 'R':
            printf("\nHEAD:%d\n", head_current_position);
            printf("\nTAPE_SIZE:%d\n", strlen(tape->data));
            if (head_current_position >= strlen(tape->data) - 1) {
                grow_str(tape);
            }
            head_current_position++;
            break;
        case 'L':
            head_current_position--;
            if (head_current_position < 0) {
                error("\nIndex out of bound error\n");
            }
            break;
        case 'H':
            break;
        case 'S':
            *is_simulating_pointer = false;
            break;
        default:
            error("\nInvalid iterator flag\n");
    }
}

static char *construct_message(const unsigned command_iterator) {
    const char *tape_data = tape->data;
    const unsigned valid_tape_size = strlen(tape_data);
    const unsigned message_capacity = LINE_BREAK_SIZE + valid_tape_size + LINE_BREAK_SIZE + valid_tape_size
                                      + LINE_BREAK_SIZE + 10 + LINE_BREAK_SIZE + 1 + 1;
    char *message = calloc(message_capacity, sizeof(char));
    message[0] = '\n';
    for (unsigned i = LINE_BREAK_SIZE; i < valid_tape_size + LINE_BREAK_SIZE; ++i) {
        message[i] = '_';
        message[valid_tape_size + LINE_BREAK_SIZE + i] = tape_data[i - 1];
    }
    message[LINE_BREAK_SIZE + valid_tape_size] = '\n';
    message[head_current_position + LINE_BREAK_SIZE] = 'V';
    message[LINE_BREAK_SIZE + valid_tape_size + valid_tape_size] = tape_data[valid_tape_size - 1];
    message[LINE_BREAK_SIZE + valid_tape_size + valid_tape_size + LINE_BREAK_SIZE] = '\n';
    message[message_capacity - 2] = '\n';
    const char *command_data = command_context->data;
    for (unsigned k = 0; k < 11; ++k) {
        message[message_capacity - 3 - k] = command_data[command_iterator + 10 - k];
    }
    return message;
}

static void simulate() {
    const unsigned command_context_size = strlen(command_context->data);
    _Bool is_simulating = true;
    while (is_simulating) {
        unsigned command_iterator = 0;
        while (true) {

            const _Bool is_eq_v = is_equals_current_value(command_iterator);
            const _Bool is_eq_s = is_equals_current_state(command_iterator);
            printf("\n%d v:\n", is_eq_v);
            printf("\n%d s:\n", is_eq_s);
            if (command_iterator >= command_context_size) {
                error("\nCommand is not found\n");
            } else if (is_eq_v && is_eq_s) {
                break;
            } else {
                command_iterator += COMMAND_SHIFT;
            }
        }
        printf("\nX:%s\n", tape->data);


        set_new_value(command_iterator);
        set_new_state(command_iterator);
        modify_iterator_flag(command_iterator, &is_simulating);


        //Work with message:
        char *message = construct_message(command_iterator);
        fputs(message, output_file);

        //Machine mode:
        if (is_debug_mode) {
            char user_message[USER_MESSAGE_MAX_SIZE];
            printf("\nEnter message:\n");
            scanf("%3s", user_message);
            if (strcmp(user_message, ">") == 0) {
                printf("%s", message);
            } else if (strcmp(user_message, ">>") == 0) {
                is_debug_mode = false;
            } else if (strcmp(user_message, "||") == 0) {
                is_simulating = false;
            } else {
                error("\nInvalid user message\n");
            }
            free(message);
        }
    }
}

void start_t_machine(
        const char *command_file_path,
        const char *input_file_path,
        const char *output_file_path
) {
    tape = create_str();
    command_context = create_str();
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
    free(tape);
    free(command_context);
}