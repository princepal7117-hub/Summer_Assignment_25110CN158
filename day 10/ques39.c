// wap to print number pyramid 

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

        // Print increasing numbers
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // Print decreasing numbers
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        printf("\n");
    }

    return 0;
}