// Write a program to Rotate array left

#include <stdio.h>

int main()
{
    int arr[100], n, i, first;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Store the first element
    first = arr[0];

    // Shift elements to the left
    for(i = 0; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    // Place the first element at the end
    arr[n - 1] = first;

    // Display rotated array
    printf("Array after left rotation:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}