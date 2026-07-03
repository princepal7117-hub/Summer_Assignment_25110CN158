// Write a program to Find missing number in array 

#include <stdio.h>

int main()
{
    int arr[100], n, i;
    int sum = 0, total, missing;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n - 1);
    for(i = 0; i < n - 1; i++)
    {
        scanf("%d", &arr[i]);
        sum = sum + arr[i];
    }

    // Sum of first n natural numbers
    total = n * (n + 1) / 2;

    // Missing number
    missing = total - sum;

    printf("Missing number = %d", missing);

    return 0;
}

