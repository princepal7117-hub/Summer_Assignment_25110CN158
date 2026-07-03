// wap to write function to check prime 

#include <stdio.h>

// Function to check prime
int isPrime(int n)
{
    int i;

    if (n <= 1)
        return 0;

    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isPrime(num))
        printf("%d is a Prime Number.", num);
    else
        printf("%d is Not a Prime Number.", num);

    return 0;
}