//wap to write function to find maximum 

#include <stdio.h>

// Function to find the maximum number
int maximum(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int main()
{
    int num1, num2, max;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    max = maximum(num1, num2);

    printf("Maximum number = %d", max);

    return 0;
}