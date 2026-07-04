// Write a program to Find maximum occurring character 

#include <stdio.h>
#include <string.h>

char maxOccurringChar(char *str) {
    int count[256] = {0};
    int len = strlen(str);

    // Count frequency of each character
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    int maxCount = 0;
    char result = str[0];

    // Find character with the highest frequency
    // (scans string order so first max-frequency char wins ties)
    for (int i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] > maxCount) {
            maxCount = count[(unsigned char)str[i]];
            result = str[i];
        }
    }

    return result;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove trailing newline if present
    str[strcspn(str, "\n")] = '\0';

    if (strlen(str) == 0) {
        printf("Empty string entered.\n");
        return 0;
    }

    char result = maxOccurringChar(str);
    printf("Maximum occurring character: %c\n", result);

    return 0;
}