// Write a program to Find longest word

#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    char longestWord[100] = "";
    char currentWord[100];
    int currentIndex = 0;
    int len = strlen(str);

    for (int i = 0; i <= len; i++) {
        // Treat space or end of string as a word delimiter
        if (str[i] == ' ' || str[i] == '\0') {
            currentWord[currentIndex] = '\0';

            if (strlen(currentWord) > strlen(longestWord)) {
                strcpy(longestWord, currentWord);
            }

            currentIndex = 0; // reset for next word
        } else {
            currentWord[currentIndex++] = str[i];
        }
    }

    printf("Longest word: %s\n", longestWord);
    printf("Length: %d\n", (int)strlen(longestWord));

    return 0;
}