// Write a program to Linear search.

#include <stdio.h>

int main()
{
    int arr[100], n, i, key, found = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Enter the element to search
    printf("Enter the element to search: ");
    scanf("%d", &key);

    // Linear Search
    for(i = 0; i < n; i++)
    {
        if(arr[i] == key)
        {
            found = 1;
            printf("Element found at position %d", i + 1);
            break;
        }
    }

    if(found == 0)
    {
        printf("Element not found.");
    }

    return 0;
}