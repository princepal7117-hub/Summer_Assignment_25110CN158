// Write a program to Frequency of an elemen

#include <stdio.h>

int main()
{
    int arr[100], n, i, key, count = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Input the element whose frequency is to be found
    printf("Enter the element to find frequency: ");
    scanf("%d", &key);

    // Count frequency
    for(i = 0; i < n; i++)
    {
        if(arr[i] == key)
        {
            count++;
        }
    }

    // Display result
    printf("Frequency of %d = %d", key, count);

    return 0;
}