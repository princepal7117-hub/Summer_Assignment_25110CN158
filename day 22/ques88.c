// Write a program to Remove spaces from string 

#include <stdio.h>

int main() {
    char str[100];
    int i, j = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove spaces
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';

    printf("String after removing spaces: %s\n", str);

    return 0;
}