#include "assembler.h"
#include "tools.h"

const int MAX_FNAME_LENGTH = 20;

int main(int argc, char *argv[]) {
    // Verifico il numero di argomenti (argc >= 2)
    if (argc < 2) {
        printf("Inserire file da assemblare (.asm)!\n");
        return 0;
    }

    // Apertura file di input
    FILE *fin = fopen(argv[1], "r");

    // Separazione nome del file da estensione
    char fname[MAX_FNAME_LENGTH];
    strncpy(fname, argv[1], strlen(argv[1]) - 4);

    // Assemblatore
    assemble(fin, fname);

    // Chiusura file di input
    fclose(fin);

    return 0;
}