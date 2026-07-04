// Write a program to Remove duplicate characters

#include <stdio.h>
#include <string.h>

void removeDuplicates(char *str) {
    int seen[256] = {0};
    int writeIndex = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)str[i];

        if (!seen[ch]) {
            seen[ch] = 1;
            str[writeIndex++] = str[i];
        }
    }

    str[writeIndex] = '\0';
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    removeDuplicates(str);

    printf("String after removing duplicates: %s\n", str);

    return 0;
}