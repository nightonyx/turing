#include <stdio.h>
#include "../headers/common.h"
#include "../headers/t_machine.h"


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
    FILE *output_file = fopen(output_file_path, WRITE_MODE);

}