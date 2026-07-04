// Write a program to Create bank account system 

#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MIN_BALANCE 500.0

struct Account {
    int accNo;
    char name[50];
    char accType[15]; // "Savings" or "Current"
    float balance;
    int isActive;
};

struct Transaction {
    int accNo;
    char type[10]; // "DEPOSIT", "WITHDRAW", "TRANSFER"
    float amount;
    float balanceAfter;
};

struct Account accounts[MAX_ACCOUNTS];
struct Transaction transactions[500];
int accountCount = 0;
int transactionCount = 0;
int nextAccNo = 1001; // auto-generated account numbers

// ---------- Lookup helpers ----------

int findAccountIndex(int accNo) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].isActive && accounts[i].accNo == accNo) {
            return i;
        }
    }
    return -1;
}

void logTransaction(int accNo, const char *type, float amount, float balanceAfter) {
    if (transactionCount >= 500) return; // simple cap, ignore overflow for this demo

    struct Transaction t;
    t.accNo = accNo;
    strcpy(t.type, type);
    t.amount = amount;
    t.balanceAfter = balanceAfter;
    transactions[transactionCount++] = t;
}

// ---------- Core operations ----------

void openAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Bank database is full!\n");
        return;
    }

    struct Account a;
    a.accNo = nextAccNo++;
    getchar();

    printf("Enter Name: ");
    fgets(a.name, 50, stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Enter Account Type (Savings/Current): ");
    fgets(a.accType, 15, stdin);
    a.accType[strcspn(a.accType, "\n")] = '\0';

    printf("Enter Initial Deposit (min %.2f): ", MIN_BALANCE);
    scanf("%f", &a.balance);

    if (a.balance < MIN_BALANCE) {
        printf("Initial deposit must be at least %.2f. Account not created.\n", MIN_BALANCE);
        return;
    }

    a.isActive = 1;
    accounts[accountCount++] = a;

    logTransaction(a.accNo, "DEPOSIT", a.balance, a.balance);

    printf("Account created successfully! Your Account Number is: %d\n", a.accNo);
}

void depositMoney() {
    int accNo;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccountIndex(accNo);
    if (index == -1) {
        printf("Account %d not found.\n", accNo);
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Deposit must be positive.\n");
        return;
    }

    accounts[index].balance += amount;
    logTransaction(accNo, "DEPOSIT", amount, accounts[index].balance);

    printf("Deposit successful. New balance: %.2f\n", accounts[index].balance);
}

void withdrawMoney() {
    int accNo;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccountIndex(accNo);
    if (index == -1) {
        printf("Account %d not found.\n", accNo);
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Withdrawal must be positive.\n");
        return;
    }

    if (accounts[index].balance - amount < MIN_BALANCE) {
        printf("Insufficient balance. Minimum balance of %.2f must be maintained.\n", MIN_BALANCE);
        printf("Available for withdrawal: %.2f\n", accounts[index].balance - MIN_BALANCE);
        return;
    }

    accounts[index].balance -= amount;
    logTransaction(accNo, "WITHDRAW", amount, accounts[index].balance);

    printf("Withdrawal successful. New balance: %.2f\n", accounts[index].balance);
}

void transferMoney() {
    int fromAcc, toAcc;
    float amount;

    printf("Enter Your Account Number: ");
    scanf("%d", &fromAcc);
    printf("Enter Recipient Account Number: ");
    scanf("%d", &toAcc);

    int fromIndex = findAccountIndex(fromAcc);
    int toIndex = findAccountIndex(toAcc);

    if (fromIndex == -1) {
        printf("Your account %d not found.\n", fromAcc);
        return;
    }
    if (toIndex == -1) {
        printf("Recipient account %d not found.\n", toAcc);
        return;
    }
    if (fromAcc == toAcc) {
        printf("Cannot transfer to the same account.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Transfer must be positive.\n");
        return;
    }

    if (accounts[fromIndex].balance - amount < MIN_BALANCE) {
        printf("Insufficient balance. Minimum balance of %.2f must be maintained.\n", MIN_BALANCE);
        return;
    }

    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;

    logTransaction(fromAcc, "TRANSFER", amount, accounts[fromIndex].balance);
    logTransaction(toAcc, "DEPOSIT", amount, accounts[toIndex].balance);

    printf("Transfer successful!\n");
    printf("Your new balance: %.2f\n", accounts[fromIndex].balance);
}

void checkBalance() {
    int accNo;
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccountIndex(accNo);
    if (index == -1) {
        printf("Account %d not found.\n", accNo);
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Account No : %d\n", accounts[index].accNo);
    printf("Name       : %s\n", accounts[index].name);
    printf("Type       : %s\n", accounts[index].accType);
    printf("Balance    : %.2f\n", accounts[index].balance);
}

void miniStatement() {
    int accNo;
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (findAccountIndex(accNo) == -1) {
        printf("Account %d not found.\n", accNo);
        return;
    }

    int found = 0;
    printf("\n--- Mini Statement for Account %d ---\n", accNo);
    printf("%-10s %-12s %-12s\n", "Type", "Amount", "Balance After");
    printf("---------------------------------------\n");

    int shown = 0;
    for (int i = transactionCount - 1; i >= 0 && shown < 5; i--) {
        if (transactions[i].accNo == accNo) {
            printf("%-10s %-12.2f %-12.2f\n",
                   transactions[i].type, transactions[i].amount, transactions[i].balanceAfter);
            found = 1;
            shown++;
        }
    }

    if (!found) {
        printf("No transactions found for this account.\n");
    }
}

void closeAccount() {
    int accNo;
    printf("Enter Account Number to close: ");
    scanf("%d", &accNo);

    int index = findAccountIndex(accNo);
    if (index == -1) {
        printf("Account %d not found.\n", accNo);
        return;
    }

    if (accounts[index].balance > 0) {
        printf("Please withdraw remaining balance (%.2f) before closing.\n", accounts[index].balance);
        return;
    }

    accounts[index].isActive = 0;
    printf("Account %d closed successfully.\n", accNo);
}

void displayAllAccounts() {
    int found = 0;
    printf("\n%-10s %-20s %-12s %-10s\n", "Acc No", "Name", "Type", "Balance");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].isActive) {
            printf("%-10d %-20s %-12s %-10.2f\n",
                   accounts[i].accNo, accounts[i].name, accounts[i].accType, accounts[i].balance);
            found = 1;
        }
    }

    if (!found) {
        printf("No active accounts found.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== BANK ACCOUNT SYSTEM =====\n");
        printf("1. Open New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Check Balance\n");
        printf("6. Mini Statement\n");
        printf("7. Close Account\n");
        printf("8. Display All Accounts\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: openAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: transferMoney(); break;
            case 5: checkBalance(); break;
            case 6: miniStatement(); break;
            case 7: closeAccount(); break;
            case 8: displayAllAccounts(); break;
            case 9: printf("Thank you for banking with us. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}