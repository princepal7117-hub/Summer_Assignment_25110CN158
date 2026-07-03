// wap to write function for perfect number 

#include <stdio.h>

// Function to check Perfect Number
int isPerfect(int n)
{
    int i, sum = 0;

    for (i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            sum = sum + i;
        }
    }

    if (sum == n)
        return 1;
    else
        return 0;
}

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isPerfect(num))
        printf("%d is a Perfect Number.", num);
    else
        printf("%d is Not a Perfect Number.", num);

    return 0;
}