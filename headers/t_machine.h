#ifndef TURING_T_MACHINE_H

#define TURING_T_MACHINE_H

#define TAPE_SIZE 1024

#define STATE_SIZE 3

#define COMMAND_CONTEXT_SIZE 1024

extern unsigned head_current_position;
extern char current_state[STATE_SIZE];
extern char tape[TAPE_SIZE];
extern char command_context[COMMAND_CONTEXT_SIZE];
extern _Bool is_debug_mode;
extern struct _iobuf *output_file;

void start_t_machine(
        const char *command_file_path,
        const char *input_file_path,
        const char *output_file_path
);

#endif //TURING_T_MACHINE_H