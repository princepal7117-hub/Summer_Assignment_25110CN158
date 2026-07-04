// Write a program to Find first repeating character 

#include <stdio.h>
#include <string.h>

char firstRepeatingChar(char *str) {
    int count[256] = {0};
    int len = strlen(str);

    // Count frequency of each character
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    // Find first character with frequency > 1
    for (int i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] > 1) {
            return str[i];
        }
    }

    return '\0'; // No repeating character found
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove trailing newline if present
    str[strcspn(str, "\n")] = '\0';

    char result = firstRepeatingChar(str);

    if (result != '\0') {
        printf("First repeating character: %c\n", result);
    } else {
        printf("No repeating character found.\n");
    }

    return 0;
}