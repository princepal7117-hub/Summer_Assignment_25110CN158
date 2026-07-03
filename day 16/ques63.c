// Write a program to Find pair with given sum.

#include <stdio.h>

int main()
{
    int arr[100], n, i, j, sum, found = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the required sum: ");
    scanf("%d", &sum);

    // Find pair with given sum
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(arr[i] + arr[j] == sum)
            {
                printf("Pair found: %d and %d\n", arr[i], arr[j]);
                found = 1;
                break;
            }
        }

        if(found)
            break;
    }

    if(found == 0)
    {
        printf("No pair found.");
    }

    return 0;
}