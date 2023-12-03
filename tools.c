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

long int pow(int b, int e) {
    long int r = 1;
    for (int i = 0; i < e; i++) {
        r *= b;
    }
    return r;
}

long int dec_to_bin(int n) {
    int digits = 0;
    long int bin = 0;
    while (n > 0) {
        int r = n % 2;
        bin += r * pow(10, digits);
        digits++;
        n /= 2;
    }
    return bin;
}