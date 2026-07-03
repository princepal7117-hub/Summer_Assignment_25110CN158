// Write a program to Find diagonal sum

#include <stdio.h>

int main()
{
    int a[10][10];
    int n, i, j, sum = 0;

    printf("Enter the order of square matrix: ");
    scanf("%d", &n);

    // Input matrix
    printf("Enter matrix elements:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    // Find sum of diagonal elements
    for(i = 0; i < n; i++)
    {
        sum = sum + a[i][i];
    }

    // Display result
    printf("Sum of diagonal elements = %d", sum);

    return 0;
}