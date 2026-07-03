// Write a program to Find column-wise sum.

#include <stdio.h>

int main()
{
    int a[10][10];
    int rows, cols, i, j, sum;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    // Input matrix
    printf("Enter matrix elements:\n");
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    // Find column-wise sum
    for(j = 0; j < cols; j++)
    {
        sum = 0;
        for(i = 0; i < rows; i++)
        {
            sum = sum + a[i][j];
        }
        printf("Sum of Column %d = %d\n", j + 1, sum);
    }

    return 0;
}