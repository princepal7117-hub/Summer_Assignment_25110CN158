// Write a program to Create quiz application

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_QUESTIONS 5

struct Question {
    char question[200];
    char options[4][50];
    char correctAnswer;
};

int main() {
    struct Question quiz[NUM_QUESTIONS] = {
        {
            "What is the capital of France?",
            {"A. Berlin", "B. Madrid", "C. Paris", "D. Rome"},
            'C'
        },
        {
            "Which language is used to program microcontrollers?",
            {"A. Python", "B. C", "C. HTML", "D. SQL"},
            'B'
        },
        {
            "What is the value of PI (approx)?",
            {"A. 2.14", "B. 3.14", "C. 4.13", "D. 1.41"},
            'B'
        },
        {
            "Who developed the C language?",
            {"A. James Gosling", "B. Guido van Rossum", "C. Dennis Ritchie", "D. Bjarne Stroustrup"},
            'C'
        },
        {
            "What does 'CPU' stand for?",
            {"A. Central Process Unit", "B. Central Processing Unit", "C. Computer Personal Unit", "D. Central Processor Utility"},
            'B'
        }
    };

    int score = 0;
    char userAnswer;

    printf("=== Welcome to the Quiz Application ===\n");
    printf("Answer each question by typing A, B, C, or D.\n\n");

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("Q%d. %s\n", i + 1, quiz[i].question);
        for (int j = 0; j < 4; j++) {
            printf("   %s\n", quiz[i].options[j]);
        }

        printf("Your answer: ");
        scanf(" %c", &userAnswer);
        userAnswer = toupper(userAnswer);

        if (userAnswer == quiz[i].correctAnswer) {
            printf("Correct!\n\n");
            score++;
        } else {
            printf("Wrong! The correct answer was %c.\n\n", quiz[i].correctAnswer);
        }
    }

    printf("=== Quiz Completed ===\n");
    printf("Your score: %d out of %d\n", score, NUM_QUESTIONS);

    float percentage = ((float)score / NUM_QUESTIONS) * 100;
    printf("Percentage: %.2f%%\n", percentage);

    if (percentage >= 80) {
        printf("Grade: Excellent!\n");
    } else if (percentage >= 60) {
        printf("Grade: Good\n");
    } else if (percentage >= 40) {
        printf("Grade: Average\n");
    } else {
        printf("Grade: Needs Improvement\n");
    }

    return 0;
}