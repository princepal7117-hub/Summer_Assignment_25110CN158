// Write a program to Sort words by length

#include <stdio.h>
#include <string.h>

void sortByLength(char words[][50], int n) {
    char temp[50];

    // Bubble sort based on string length
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strlen(words[j]) > strlen(words[j + 1])) {
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of words: ");
    scanf("%d", &n);
    getchar(); // consume leftover newline from scanf

    char words[n][50];

    printf("Enter %d words:\n", n);
    for (int i = 0; i < n; i++) {
        fgets(words[i], 50, stdin);
        words[i][strcspn(words[i], "\n")] = '\0';
    }

    sortByLength(words, n);

    printf("\nWords sorted by length:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}