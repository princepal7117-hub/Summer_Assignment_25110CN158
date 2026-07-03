// wap to write function for armstrong 

#include <stdio.h>
#include <math.h>

// Function to check Armstrong number
int isArmstrong(int n)
{
    int original, rem, digits = 0;
    int sum = 0, temp;

    original = n;
    temp = n;

    // Count number of digits
    while (temp != 0)
    {
        digits++;
        temp = temp / 10;
    }

    temp = n;

    // Calculate sum of digits raised to the power of digits
    while (temp != 0)
    {
        rem = temp % 10;
        sum = sum + pow(rem, digits);
        temp = temp / 10;
    }

    if (sum == original)
        return 1;
    else
        return 0;
}

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num))
        printf("%d is an Armstrong Number.", num);
    else
        printf("%d is Not an Armstrong Number.", num);

    return 0;
}