// wap to check strong number 

#include <stdio.h>

int main() {
    int num, temp, rem, i;
    int sum = 0, fact;

    printf("Enter a number: ");
    scanf("%d", &num);

    temp = num;

    while (temp != 0) {
        rem = temp % 10;
        fact = 1;

        for (i = 1; i <= rem; i++) {
            fact = fact * i;
        }

        sum = sum + fact;
        temp = temp / 10;
    }

    if (sum == num)
        printf("%d is a Strong Number.", num);
    else
        printf("%d is Not a Strong Number.", num);

    return 0;
}