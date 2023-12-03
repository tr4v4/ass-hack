#include "tools.h"

int strlen(char str[]) {
    int index = 0;
    while (str[index] != '\0') index++;
    return index;
}

void strncpy(char dest[], char src[], int max_index) {
    // Precondition: max_index < strlen(src)
    int index = 0;
    while (index < max_index) {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
}

long int dec_to_bin(int n, int *digits) {
    
}