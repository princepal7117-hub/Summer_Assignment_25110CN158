#include <stdio.h>

int main()
{
    int arr[100], n, i, sum = 0;
    float avg;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        sum = sum + arr[i];
    }

    // Calculate average
    avg = (float)sum / n;

    // Display result
    printf("Sum = %d\n", sum);
    printf("Average = %.2f", avg);

    return 0;
}