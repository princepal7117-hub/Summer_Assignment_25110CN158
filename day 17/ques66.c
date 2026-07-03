// Write a program to Union of arrays

#include <stdio.h>

int main()
{
    int arr1[100], arr2[100], unionArr[200];
    int n1, n2, i, j, k = 0, found;

    printf("Enter the number of elements in first array: ");
    scanf("%d", &n1);

    printf("Enter %d elements:\n", n1);
    for(i = 0; i < n1; i++)
    {
        scanf("%d", &arr1[i]);
        unionArr[k++] = arr1[i];
    }

    printf("Enter the number of elements in second array: ");
    scanf("%d", &n2);

    printf("Enter %d elements:\n", n2);
    for(i = 0; i < n2; i++)
    {
        scanf("%d", &arr2[i]);

        found = 0;
        for(j = 0; j < k; j++)
        {
            if(arr2[i] == unionArr[j])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            unionArr[k++] = arr2[i];
        }
    }

    printf("Union of arrays:\n");
    for(i = 0; i < k; i++)
    {
        printf("%d ", unionArr[i]);
    }

    return 0;
}