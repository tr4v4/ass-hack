#include "symbol_table.h"
#include "tools.h"

symtable *init() {
    symtable *st = NULL;
    st = insert(st, (char *)"R0", 0);
    st = insert(st, (char *)"R1", 1);
    st = insert(st, (char *)"R2", 2);
    st = insert(st, (char *)"R3", 3);
    st = insert(st, (char *)"R4", 4);
    st = insert(st, (char *)"R5", 5);
    st = insert(st, (char *)"R6", 6);
    st = insert(st, (char *)"R7", 7);
    st = insert(st, (char *)"R8", 8);
    st = insert(st, (char *)"R9", 9);
    st = insert(st, (char *)"R10", 10);
    st = insert(st, (char *)"R11", 11);
    st = insert(st, (char *)"R12", 12);
    st = insert(st, (char *)"R13", 13);
    st = insert(st, (char *)"R14", 14);
    st = insert(st, (char *)"R15", 15);
    st = insert(st, (char *)"SCREEN", 16384);
    st = insert(st, (char *)"KBD", 24576);
    st = insert(st, (char *)"SP", 0);
    st = insert(st, (char *)"LCL", 1);
    st = insert(st, (char *)"ARG", 2);
    st = insert(st, (char *)"THIS", 3);
    st = insert(st, (char *)"THAT", 4);
    return st;
}

symtable *insert(symtable *st, char symbol[], int value) {
    symtable *tmp = new symtable;
    strncpy(tmp->symbol, symbol, MAX_SYMBOL_LENGTH);
    tmp->value = value;
    tmp->next = st;
    return tmp;
}

int search(symtable *st, char symbol[]) {
    bool found = false;
    while (st != NULL && !found) {
        if (strncmp(st->symbol, symbol)) found = true;
        else st = st->next;
    }
    if (found) return st->value;
    else return -1;
}