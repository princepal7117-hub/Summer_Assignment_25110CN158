// Write a program to Find common elements

#include <stdio.h>

int main()
{
    int arr1[100], arr2[100];
    int n1, n2, i, j, found;

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

    printf("Common elements are:\n");

    for(i = 0; i < n1; i++)
    {
        found = 0;

        for(j = 0; j < n2; j++)
        {
            if(arr1[i] == arr2[j])
            {
                found = 1;
                break;
            }
        }

        if(found)
        {
            printf("%d ", arr1[i]);
        }
    }

    return 0;
}