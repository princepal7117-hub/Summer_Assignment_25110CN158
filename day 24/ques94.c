// Write a program to Compress a string.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* compressString(char *str) {
    int len = strlen(str);

    if (len == 0) {
        char *empty = (char *)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    // Worst case: no compression benefit, so allocate generously
    // (each char could need itself + a multi-digit count)
    char *result = (char *)malloc(2 * len + 1);
    int resultIndex = 0;

    int count = 1;
    for (int i = 1; i <= len; i++) {
        if (i < len && str[i] == str[i - 1]) {
            count++;
        } else {
            result[resultIndex++] = str[i - 1];
            // Append the count as digits
            char countStr[12];
            sprintf(countStr, "%d", count);
            for (int j = 0; countStr[j] != '\0'; j++) {
                result[resultIndex++] = countStr[j];
            }
            count = 1;
        }
    }
    result[resultIndex] = '\0';

    return result;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    char *compressed = compressString(str);

    printf("Compressed string: %s\n", compressed);

    free(compressed);
    return 0;
}