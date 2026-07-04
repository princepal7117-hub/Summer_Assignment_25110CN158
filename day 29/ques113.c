/*Write a program to Create menu-driven
calculator.*/

#include <stdio.h>
#include <math.h>

int main() {
    int choice;
    double num1, num2, result;

    do {
        printf("\n===== MENU-DRIVEN CALCULATOR =====\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Modulus (integer)\n");
        printf("6. Power (x^y)\n");
        printf("7. Square Root\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 8) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        if (choice == 7) {
            printf("Enter a number: ");
            scanf("%lf", &num1);

            if (num1 < 0) {
                printf("Error: Cannot compute square root of a negative number.\n");
            } else {
                result = sqrt(num1);
                printf("Result: sqrt(%.2f) = %.4f\n", num1, result);
            }
            continue;
        }

        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        printf("Enter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("Result: %.2f + %.2f = %.2f\n", num1, num2, result);
                break;

            case 2:
                result = num1 - num2;
                printf("Result: %.2f - %.2f = %.2f\n", num1, num2, result);
                break;

            case 3:
                result = num1 * num2;
                printf("Result: %.2f * %.2f = %.2f\n", num1, num2, result);
                break;

            case 4:
                if (num2 == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    result = num1 / num2;
                    printf("Result: %.2f / %.2f = %.4f\n", num1, num2, result);
                }
                break;

            case 5:
                if ((int)num2 == 0) {
                    printf("Error: Modulus by zero is not allowed.\n");
                } else {
                    printf("Result: %d %% %d = %d\n", (int)num1, (int)num2, (int)num1 % (int)num2);
                }
                break;

            case 6:
                result = pow(num1, num2);
                printf("Result: %.2f ^ %.2f = %.4f\n", num1, num2, result);
                break;
        }

    } while (choice != 8);

    return 0;
}