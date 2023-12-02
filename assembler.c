#include "assembler.h"

const int MAX_LINE_LENGTH = 100;
const int MAX_INSTRUCTION_LENGTH = 10;
const int MAX_DEST_LENGTH = 3;
const int MAX_COMP_LENGTH = 3;
const int MAX_JMP_LENGTH = 3;
const int BINARY_INSTRUCTION_LENGTH = 16;

typedef struct A_instruction {
    int value;
} A_instruction;

typedef struct C_instruction {
    char dest[MAX_DEST_LENGTH];
    char comp[MAX_COMP_LENGTH];
    char jmp[MAX_JMP_LENGTH];
} C_instruction;

void clear_line(char line[], char instruction[]) {
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
}

int identify_instruction(char instruction[]) {
    if (instruction[0] == '/' && instruction[1] == '/') return 0;
    if (instruction[0] == '@') return 1;
    return 2;
}

A_instruction *parse_A_instruction(char instruction[]) {
    A_instruction *a = (A_instruction *)malloc(sizeof(A_instruction));
    // TODO
    return a;
}

C_instruction *parse_C_instruction(char instruction[]) {
    C_instruction *c = (C_instruction *)malloc(sizeof(C_instruction));
    // TODO
    return c;
}

void assemble(FILE *fin, char fname[]) {
    // Apertura file di output
    sprintf(fname, "%s.hack", fname);
    FILE *fout = fopen(fname, "w");

    // Scorro ogni riga del file di input
    while (!feof(fin)) {
        char line[MAX_LINE_LENGTH];
        fgets(line, MAX_LINE_LENGTH, fin);

        if (line[0] != '\n') {
            char instruction[MAX_INSTRUCTION_LENGTH + 1];

            // Pulisco ogni riga non vuota
            clear_line(line, instruction);

            // Identifico ogni istruzione (commento, A-instruction,
            // C-instruction)
            int type = identify_instruction(instruction);

            // Considero solo A-instruction e C-instruction
            char binary_instruction[BINARY_INSTRUCTION_LENGTH + 1];
            if (type == 1) {
                A_instruction *a_in = parse_A_instruction(instruction);
                convert_A_instruction(binary_instruction, a_in);
            } else if (type == 2) {
                C_instruction *c_in = parse_C_instruction(instruction);
                convert_C_instruction(binary_instruction, c_in);
            }

            // Scrivo l'istruzione in binario nel file di output
            fputs(binary_instruction, fout);

            printf("%s\t%d\n", instruction, type);
        }
    }

    // Chiusura file di output
    fclose(fout);
}