// Write a program to Create number guessing gaming 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secretNumber, guess, attempts = 0;
    int lowerBound = 1, upperBound = 100;

    // Seed random number generator with current time
    srand(time(0));
    secretNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

    printf("=== Number Guessing Game ===\n");
    printf("I'm thinking of a number between %d and %d.\n", lowerBound, upperBound);

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("\nCongratulations! You guessed it right!\n");
            printf("The number was %d.\n", secretNumber);
            printf("It took you %d attempt%s.\n", attempts, (attempts == 1) ? "" : "s");
        }

    } while (guess != secretNumber);

    return 0;
}