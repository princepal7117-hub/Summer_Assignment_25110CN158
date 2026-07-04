//Write a program to Count words in a sentence 

#include <stdio.h>

int main() {
    char str[100];
    int i = 0, words = 0;

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    while (str[i] != '\0') {
        // Count a word when a non-space character is followed by a space, newline, or end of string
        if ((str[i] != ' ' && str[i] != '\n') &&
            (str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0')) {
            words++;
        }
        i++;
    }

    printf("Number of words = %d\n", words);

    return 0;
}