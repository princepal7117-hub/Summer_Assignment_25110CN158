//Write a program to Check string rotation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isRotation(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Lengths must match, and empty strings are trivially rotations
    if (len1 != len2) {
        return 0;
    }
    if (len1 == 0) {
        return 1;
    }

    // Concatenate str1 with itself: "ABCD" -> "ABCDABCD"
    char *temp = (char *)malloc(2 * len1 + 1);
    strcpy(temp, str1);
    strcat(temp, str1);

    // If str2 is a substring of temp, str1 is a rotation of str2
    int result = (strstr(temp, str2) != NULL);

    free(temp);
    return result;
}

int main() {
    char str1[100], str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';

    if (isRotation(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are NOT rotations of each other.\n");
    }

    return 0;
}