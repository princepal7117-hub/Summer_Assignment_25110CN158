/*Write a program to Create voting eligibility
system*/

#include <stdio.h>

struct Voter {
    char name[50];
    int age;
    int hasVoterID;
};

int checkEligibility(struct Voter v) {
    // Must be 18 or older AND have a valid voter ID
    if (v.age >= 18 && v.hasVoterID) {
        return 1; // Eligible
    }
    return 0; // Not eligible
}

int main() {
    int n;

    printf("Enter number of voters to check: ");
    scanf("%d", &n);
    getchar(); // consume leftover newline

    struct Voter voters[n];

    for (int i = 0; i < n; i++) {
        printf("\n--- Voter %d ---\n", i + 1);

        printf("Enter name: ");
        fgets(voters[i].name, 50, stdin);
        voters[i].name[strcspn(voters[i].name, "\n")] = '\0';

        printf("Enter age: ");
        scanf("%d", &voters[i].age);

        printf("Do you have a voter ID? (1 = Yes, 0 = No): ");
        scanf("%d", &voters[i].hasVoterID);
        getchar(); // consume leftover newline before next fgets
    }

    printf("\n=== Eligibility Results ===\n");
    int eligibleCount = 0;

    for (int i = 0; i < n; i++) {
        printf("\nName: %s\n", voters[i].name);
        printf("Age: %d\n", voters[i].age);

        if (checkEligibility(voters[i])) {
            printf("Status: ELIGIBLE to vote\n");
            eligibleCount++;
        } else {
            printf("Status: NOT ELIGIBLE to vote\n");

            // Give a specific reason
            if (voters[i].age < 18) {
                printf("Reason: Must be at least 18 years old (currently %d)\n", voters[i].age);
            }
            if (!voters[i].hasVoterID) {
                printf("Reason: Voter ID required\n");
            }
        }
    }

    printf("\n=== Summary ===\n");
    printf("Total voters checked: %d\n", n);
    printf("Eligible: %d\n", eligibleCount);
    printf("Not eligible: %d\n", n - eligibleCount);

    return 0;
}