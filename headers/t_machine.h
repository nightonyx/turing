#ifndef TURING_T_MACHINE_H

#define TURING_T_MACHINE_H

#define TAPE_SIZE 1024

#define STATE_SIZE 3

#define CONTEXT_SIZE 1024

unsigned head_current_position = 0;
char current_state[STATE_SIZE];
char tape[TAPE_SIZE];
char command_context[CONTEXT_SIZE];
_Bool is_debug_mode = 0;
struct _iobuf *output_file;

void start_t_machine(
        const char *command_file_path,
        const char *input_file_path,
        const char *output_file_path
);

#endif //TURING_T_MACHINE_H