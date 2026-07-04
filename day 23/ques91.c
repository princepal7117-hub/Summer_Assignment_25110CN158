// Write a program to Check anagram strings

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isAnagram(char *str1, char *str2) {
    int count[256] = {0};
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // If lengths differ, they can't be anagrams
    if (len1 != len2) {
        return 0;
    }

    // Increment count for each character in str1
    for (int i = 0; i < len1; i++) {
        count[(unsigned char)tolower(str1[i])]++;
    }

    // Decrement count for each character in str2
    for (int i = 0; i < len2; i++) {
        count[(unsigned char)tolower(str2[i])]--;
    }

    // If all counts are zero, they are anagrams
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str1[100], str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';

    if (isAnagram(str1, str2)) {
        printf("The strings are anagrams.\n");
    } else {
        printf("The strings are NOT anagrams.\n");
    }

    return 0;
}