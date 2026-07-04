// Write a program to Create ATM simulation

#include <stdio.h>
#include <stdlib.h>

#define CORRECT_PIN 1234

int main() {
    float balance = 5000.0;
    int pin, attempts = 0;
    int choice;
    float amount;

    printf("=== Welcome to the ATM ===\n");

    // PIN verification (max 3 attempts)
    while (attempts < 3) {
        printf("Enter your 4-digit PIN: ");
        scanf("%d", &pin);

        if (pin == CORRECT_PIN) {
            printf("PIN accepted.\n");
            break;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts remaining: %d\n", 3 - attempts);
        }
    }

    if (attempts == 3) {
        printf("Too many incorrect attempts. Card blocked.\n");
        return 0;
    }

    // Main ATM menu loop
    do {
        printf("\n===== ATM MENU =====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Your current balance: %.2f\n", balance);
                break;

            case 2:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                if (amount <= 0) {
                    printf("Invalid amount. Deposit must be positive.\n");
                } else {
                    balance += amount;
                    printf("Deposit successful. New balance: %.2f\n", balance);
                }
                break;

            case 3:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                if (amount <= 0) {
                    printf("Invalid amount. Withdrawal must be positive.\n");
                } else if (amount > balance) {
                    printf("Insufficient balance. Your balance is %.2f\n", balance);
                } else {
                    balance -= amount;
                    printf("Withdrawal successful. New balance: %.2f\n", balance);
                }
                break;

            case 4:
                printf("Thank you for using the ATM. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}