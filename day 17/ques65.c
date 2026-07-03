//Write a program to Merge arrays.

#include <stdio.h>

int main()
{
    int arr1[100], arr2[100], arr3[200];
    int n1, n2, i, j;

    printf("Enter the number of elements in first array: ");
    scanf("%d", &n1);

    printf("Enter %d elements:\n", n1);
    for(i = 0; i < n1; i++)
    {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the number of elements in second array: ");
    scanf("%d", &n2);

    printf("Enter %d elements:\n", n2);
    for(i = 0; i < n2; i++)
    {
        scanf("%d", &arr2[i]);
    }

    // Copy first array into third array
    for(i = 0; i < n1; i++)
    {
        arr3[i] = arr1[i];
    }

    // Copy second array into third array
    for(j = 0; j < n2; j++)
    {
        arr3[i] = arr2[j];
        i++;
    }

    // Display merged array
    printf("Merged Array:\n");
    for(i = 0; i < n1 + n2; i++)
    {
        printf("%d ", arr3[i]);
    }

    return 0;
}