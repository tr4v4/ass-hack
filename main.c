#include "assembler.h"


int main(int argc, char *argv[]) {
    // Verifico il numero di argomenti (argc >= 2)
    if (argc < 2) {
        printf("Inserire file da assemblare (.asm)!\n");
        return 0;
    }

    // Apertura file di input
    FILE *fin;
    fin = fopen(argv[1], "r");

    // Assemblatore
    assemble(fin);

    // Chiusura file di input
    fclose(fin);

    return 0;
}