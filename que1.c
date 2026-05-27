//Write a program to Calculate sum of first N
//natural numbers 

#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int sum = n * (n + 1) / 2;
    printf("Sum of first %d natural numbers is: %d", n, sum);

    return 0;
}