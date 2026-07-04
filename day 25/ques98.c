// Write a program to Find common characters in strings 

#include <stdio.h>
#include <string.h>

void findCommonChars(char *str1, char *str2) {
    int count1[256] = {0};
    int count2[256] = {0};

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Count frequency of each character in both strings
    for (int i = 0; i < len1; i++) {
        count1[(unsigned char)str1[i]]++;
    }
    for (int i = 0; i < len2; i++) {
        count2[(unsigned char)str2[i]]++;
    }

    printf("Common characters: ");
    int found = 0;

    for (int i = 0; i < 256; i++) {
        if (count1[i] > 0 && count2[i] > 0) {
            // Print the character as many times as it appears in both (minimum count)
            int minCount = (count1[i] < count2[i]) ? count1[i] : count2[i];
            for (int j = 0; j < minCount; j++) {
                printf("%c ", i);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("None");
    }
    printf("\n");
}

int main() {
    char str1[100], str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';

    findCommonChars(str1, str2);

    return 0;
}