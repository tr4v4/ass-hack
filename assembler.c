#include "assembler.h"

const int MAX_LINE_LENGTH = 100;
const int MAX_INSTRUCTION_LENGTH = 10;

void clear_line(char line[], char instruction[], int *instruction_length) {
    int line_index = 0;
    int instruction_index = 0;

    // Inserisco in instruction i caratteri di line eccetto SPACE e TAB
    while (line[line_index] != '\0' &&
           instruction_index < MAX_INSTRUCTION_LENGTH) {
        if (line[line_index] != ' ' && line[line_index] != '\t' &&
            line[line_index] != '\n') {
            instruction[instruction_index] = line[line_index];
            instruction_index++;
        }
        line_index++;
    }

    // Inserisco in instruction '\0'
    instruction[instruction_index] = '\0';

    *instruction_length = instruction_index;
}

void assemble(FILE *in) {
    // Scorro ogni riga
    while (!feof(in)) {
        char line[MAX_LINE_LENGTH];
        fgets(line, MAX_LINE_LENGTH, in);

        if (line[0] != '\n') {
            char instruction[MAX_INSTRUCTION_LENGTH + 1];
            int instruction_length = 0;

            // Pulisco ogni riga non vuota
            clear_line(line, instruction, &instruction_length);

            // Identifico ogni istruzione (commento, A-instruction,
            // C-instruction)
            int type = identify_instruction(instruction);

            printf("%s\t%d\n", instruction, instruction_length);
        }
    }
}