const int MAX_SYMBOL_LENGTH = 20;

typedef struct symtable {
    char symbol[MAX_SYMBOL_LENGTH];
    int value;
    struct symtable *next;
} symtable;

symtable *init();
symtable *insert(symtable *st, char symbol[], int value);
int search(symtable *st, char symbol[]);