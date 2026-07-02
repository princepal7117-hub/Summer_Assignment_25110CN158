// wap tp find nth fibonacci term 

#include <stdio.h>

int main() {
    int n, i;
    int a = 0, b = 1, c;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n == 1)
        printf("The %dst Fibonacci term is %d", n, a);
    else if (n == 2)
        printf("The %dnd Fibonacci term is %d", n, b);
    else {
        for (i = 3; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        printf("The %dth Fibonacci term is %d", n, c);
    }

    return 0;
}