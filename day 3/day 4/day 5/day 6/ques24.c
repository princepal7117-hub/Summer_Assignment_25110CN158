// wap to find x^n without pow()

#include <stdio.h>

int main() {
    int x, n, i;
    long long result = 1;

    printf("Enter the value of x: ");
    scanf("%d", &x);

    printf("Enter the value of n: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        result = result * x;
    }

    printf("%d^%d = %lld", x, n, result);

    return 0;
}