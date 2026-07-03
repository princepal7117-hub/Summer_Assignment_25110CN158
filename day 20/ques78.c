// Write a program to Check symmetric matrix

#include <stdio.h>

int main()
{
    int a[10][10];
    int n, i, j, flag = 1;

    printf("Enter the order of the square matrix: ");
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

    // Check symmetric
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(a[i][j] != a[j][i])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 0)
            break;
    }

    if(flag == 1)
        printf("Matrix is Symmetric.");
    else
        printf("Matrix is Not Symmetric.");

    return 0;
}