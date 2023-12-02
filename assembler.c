#include "assembler.h"

void assemble(FILE *in) {
    // test
    while (!feof(in)) {
        char str[100];
        fgets(str, 100, in);
        printf("%s", str);
    }
}