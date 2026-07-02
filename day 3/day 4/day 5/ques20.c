//wap to find largest prime factor 

#include <stdio.h>

int main() {
    int num, i, largestPrimeFactor = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    while (num % 2 == 0) {
        largestPrimeFactor = 2;
        num = num / 2;
    }

    for (i = 3; i * i <= num; i += 2) {
        while (num % i == 0) {
            largestPrimeFactor = i;
            num = num / i;
        }
    }

    if (num > 2)
        largestPrimeFactor = num;

    printf("Largest Prime Factor = %d", largestPrimeFactor);

    return 0;
}