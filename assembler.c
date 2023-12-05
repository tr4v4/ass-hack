#include "assembler.h"
#include "tools.h"

const int MAX_LINE_LENGTH = 100;
const int MAX_INSTRUCTION_LENGTH = 11;
const int MAX_VALUE_LENGTH = 15;
const int MAX_C_LENGTH = 3;
const int BINARY_INSTRUCTION_LENGTH = 16;

typedef struct A_instruction {
    char value[MAX_VALUE_LENGTH+1];
} A_instruction;

typedef struct C_instruction {
    char dest[MAX_C_LENGTH+1];
    char comp[MAX_C_LENGTH+1];
    char jmp[MAX_C_LENGTH+1];
} C_instruction;

void clear_line(char line[], char instruction[]) {
    int line_index = 0;
    int instruction_index = 0;

    // Inserisco in instruction i caratteri di line eccetto SPACE, TAB e '\n'
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

void add_n_zeros(char src[], char dest[], int n) {
    // Precondition: n + strlen(src) = strlen(dest)
    // Inserisco n zeri in dest
    int dest_index = 0;
    for (dest_index; dest_index < n; dest_index++) dest[dest_index] = '0';

    // Inserisco ogni cifra di src in dest
    int src_index = 0;
    while (src[src_index] != '\0') {
        dest[dest_index] = src[src_index];
        dest_index++;
        src_index++;
    }

    dest[dest_index] = '\0';
}

A_instruction *parse_A_instruction(char instruction[]) {
    A_instruction *a = (A_instruction *)malloc(sizeof(A_instruction));

    // Elimina la chiocciola (primo carattere) dall'istruzione
    char instruction_no_at[MAX_INSTRUCTION_LENGTH + 1];
    int index_no_at = 0;
    while (instruction[index_no_at + 1] != '\0') {
        instruction_no_at[index_no_at] = instruction[index_no_at + 1];
        index_no_at++;
    }
    instruction_no_at[index_no_at] = '\0';

    // Converti in intero la stringa
    int dec = atoi(instruction_no_at);

    // Attenzione: il numero non può essere maggiore di (2^15) - 1
    if (dec > 32767)
        return NULL;
    else {
        // Converti in binario il numero
        long int bin = dec_to_bin(dec);

        // Riconverti in stringa il numero binario
        char sbin[MAX_VALUE_LENGTH + 1];
        sprintf(sbin, "%ld", bin);

        // Aggiungi gli 0 mancanti
        char sbin_complete[MAX_VALUE_LENGTH + 1];
        add_n_zeros(sbin, sbin_complete, MAX_VALUE_LENGTH - strlen(sbin));

        // Copia il numero binario nella A-instruction
        strncpy(a->value, sbin_complete, MAX_VALUE_LENGTH);

        return a;
    }
}

void convert_A_instruction(char sbin[], A_instruction *a) {
    sbin[0] = '0';
    for (int i = 0; i < MAX_VALUE_LENGTH; i++) sbin[i + 1] = a->value[i];
    sbin[BINARY_INSTRUCTION_LENGTH] = '\0';
    printf("%s\n", sbin);
}

C_instruction *parse_C_instruction(char instruction[]) {
    C_instruction *c = (C_instruction *)malloc(sizeof(C_instruction));
    
    int eq_index = find_character(instruction, '=');
    int sc_index = find_character(instruction, ';');

    // Se non è stato trovato né '=' né ';' --> errore
    if (eq_index == -1 && sc_index == -1) return NULL;

    if (eq_index != -1) {
        strncpy(c->dest, instruction, eq_index);
        if (sc_index != -1) {
            strncpy_range(c->comp, instruction, eq_index+1, sc_index);
            strncpy_range(c->jmp, instruction, sc_index+1, strlen(instruction));
        } else {
            strncpy_range(c->comp, instruction, eq_index+1, strlen(instruction));
        }
    } else {
        strncpy(c->comp, instruction, sc_index);
        if (sc_index != -1) {
            strncpy_range(c->jmp, instruction, sc_index+1, strlen(instruction));
        }
    }

    return c;
}

void convert_C_instruction(char sbin[], C_instruction *c) {
    // TODO
    printf("%s\t%s\t%s\n", c->dest, c->comp, c->jmp);
}

void assemble(FILE *fin, char fname[]) {
    // Apertura file di output
    sprintf(fname, "%s.hack", fname);
    FILE *fout = fopen(fname, "w");

    // Scorro ogni riga del file di input
    while (!feof(fin)) {
        char line[MAX_LINE_LENGTH + 1];
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
                // TODO: inserire controllo errore valore non valido (a_in = NULL)
                convert_A_instruction(binary_instruction, a_in);
            } else if (type == 2) {
                C_instruction *c_in = parse_C_instruction(instruction);
                convert_C_instruction(binary_instruction, c_in);
            }

            if (type == 1) {
                // Scrivo l'istruzione in binario nel file di output
                fputs(binary_instruction, fout);
                fputs("\n", fout);
            }

            // printf("%s\t%d\n", instruction, type);
        }
    }

    // Chiusura file di output
    fclose(fout);
}