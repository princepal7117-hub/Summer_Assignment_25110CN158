// Write a program to Sort names alphabetically 

#include <stdio.h>
#include <string.h>

void sortNames(char names[][50], int n) {
    char temp[50];

    // Bubble sort using strcmp for comparison
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of names: ");
    scanf("%d", &n);
    getchar(); // consume leftover newline from scanf

    char names[n][50];

    printf("Enter %d names:\n", n);
    for (int i = 0; i < n; i++) {
        fgets(names[i], 50, stdin);
        names[i][strcspn(names[i], "\n")] = '\0';
    }

    sortNames(names, n);

    printf("\nNames in alphabetical order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}