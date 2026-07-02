// wap to print character pyramid 

#include <stdio.h>

int main() {
    int i, j, n;

    printf("Enter the number of rows: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {

        // Print spaces
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // Print increasing characters
        for (j = 1; j <= i; j++) {
            printf("%c", 'A' + j - 1);
        }

        // Print decreasing characters
        for (j = i - 1; j >= 1; j--) {
            printf("%c", 'A' + j - 1);
        }

        printf("\n");
    }

    return 0;
}