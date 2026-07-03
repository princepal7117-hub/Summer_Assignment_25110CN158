// Write a program to Binary search.

#include <stdio.h>

int main()
{
    int arr[100], n, i;
    int key, low, high, mid, found = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input sorted array
    printf("Enter %d elements in sorted order:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search: ");
    scanf("%d", &key);

    low = 0;
    high = n - 1;

    // Binary Search
    while(low <= high)
    {
        mid = (low + high) / 2;

        if(arr[mid] == key)
        {
            found = 1;
            printf("Element found at position %d", mid + 1);
            break;
        }
        else if(arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if(found == 0)
    {
        printf("Element not found.");
    }

    return 0;
}