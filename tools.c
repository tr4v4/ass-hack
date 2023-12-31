#include "tools.h"

int strlen(char str[]) {
    int index = 0;
    while (str[index] != '\0') index++;
    return index;
}

void strncpy(char dest[], char src[], int max_index) {
    // Precondition: max_index < strlen(src)
    int index;
    for (index = 0; index < max_index; index++) dest[index] = src[index];
    dest[index] = '\0';
}

void strncpy_range(char dest[], char src[], int min_index, int max_index) {
    int index = 0;
    for (min_index; min_index < max_index; min_index++) {
        dest[index] = src[min_index];
        index++;
    }
    dest[index] = '\0';
}

void strncpy_dest_range(char dest[], char src[], int min_index, int max_index) {
    int index = 0;
    for (min_index; min_index < max_index; min_index++) {
        dest[min_index] = src[index];
        index++;
    }
}

bool strncmp(char a[], char b[]) {
    if (strlen(a) != strlen(b)) return false;
    bool equal = true;
    int index = 0;
    while (index < strlen(a) && equal) {
        if (a[index] != b[index]) equal = false;
        index++;
    }
    return equal;
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

int find_character(char a[], char c) {
    int index = 0;
    bool found = false;

    while (a[index] != '\0' && !found) {
        if (a[index] == c)
            found = true;
        else
            index++;
    }

    if (found)
        return index;
    else
        return -1;
}

bool is_number(char a[]) {
    bool number = true;
    int index = 0;
    while (a[index] != '\0' && number) {
        if (a[index] < 48 || a[index] > 57) number = false;
        else index++;
    }
    return number;
}