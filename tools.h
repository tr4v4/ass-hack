#include <stdio.h>

#include <cstdlib>

int strlen(char str[]);
void strncpy(char dest[], char src[], int max_index);
void strncpy_range(char dest[], char src[], int min_index, int max_index);
void strncpy_dest_range(char dest[], char src[], int min_index, int max_index);
bool strncmp(char a[], char b[]);
long int pow(int b, int e);
long int dec_to_bin(int n);
int find_character(char a[], char c);