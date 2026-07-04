//Write a program to Character frequency.

#include <stdio.h>

int main() {
    char str[100];
    int freq[256] = {0};
    int i;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Count frequency of each character
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\n') {
            freq[(unsigned char)str[i]]++;
        }
    }

    printf("Character Frequencies:\n");

    // Display frequency of each character
    for (i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            printf("%c = %d\n", i, freq[i]);
        }
    }

    return 0;
}