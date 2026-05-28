//Write a program to Find factorial of a number

#include <stdio.h>

int main() {
    int num, i;
    long long factorial = 1;

    printf("Enter a number: ");
    scanf("%d", &num);

    for(i = 1; i <= num; i++) {
        factorial *= i;
    }

    printf("Factorial of %d is %lld", num, factorial);

    return 0;
}