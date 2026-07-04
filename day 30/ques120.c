/*Write a program to Develop complete mini
project using arrays, strings and functions*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 3
#define NAME_LEN 50

// ---------- Function declarations ----------
int inputStudents(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS]);
float calculateTotal(float subjectMarks[], int n);
float calculateAverage(float total, int n);
char calculateGrade(float average);
void displayHeader();
void displayStudent(int roll, char name[], float marks[], float total, float avg, char grade);
void displayAll(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count);
int linearSearchByRoll(int rollNo[], int count, int key);
void searchStudent(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count);
void sortByAverage(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count);
void toUpperCase(char str[]);
void classStatistics(char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count);
void findTopper(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count);

int main() {
    int rollNo[MAX_STUDENTS];
    char names[MAX_STUDENTS][NAME_LEN];
    float marks[MAX_STUDENTS][NUM_SUBJECTS];
    int count = 0;
    int choice;

    do {
        printf("\n===== STUDENT RESULT PROCESSING SYSTEM =====\n");
        printf("1. Add Students\n");
        printf("2. Display All Results\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Sort by Average (Descending)\n");
        printf("5. Class Statistics\n");
        printf("6. Find Topper\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                count = inputStudents(rollNo, names, marks);
                break;
            case 2:
                displayAll(rollNo, names, marks, count);
                break;
            case 3:
                searchStudent(rollNo, names, marks, count);
                break;
            case 4:
                sortByAverage(rollNo, names, marks, count);
                printf("Sorted successfully!\n");
                displayAll(rollNo, names, marks, count);
                break;
            case 5:
                classStatistics(names, marks, count);
                break;
            case 6:
                findTopper(rollNo, names, marks, count);
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

// ---------- Function definitions ----------

// Takes input for multiple students; returns the count entered
int inputStudents(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS]) {
    int n;
    printf("How many students to add (max %d)? ", MAX_STUDENTS);
    scanf("%d", &n);

    if (n > MAX_STUDENTS) {
        n = MAX_STUDENTS;
        printf("Capped to %d students.\n", MAX_STUDENTS);
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Student %d ---\n", i + 1);

        printf("Roll Number: ");
        scanf("%d", &rollNo[i]);
        getchar();

        printf("Name: ");
        fgets(names[i], NAME_LEN, stdin);
        names[i][strcspn(names[i], "\n")] = '\0';

        for (int j = 0; j < NUM_SUBJECTS; j++) {
            do {
                printf("Marks in Subject %d (0-100): ", j + 1);
                scanf("%f", &marks[i][j]);
            } while (marks[i][j] < 0 || marks[i][j] > 100);
        }
    }

    printf("\n%d student record(s) added successfully!\n", n);
    return n;
}

// Sums an array of marks; demonstrates a function operating on an array parameter
float calculateTotal(float subjectMarks[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += subjectMarks[i];
    }
    return sum;
}

// Simple derived calculation, kept as its own function for clarity/reuse
float calculateAverage(float total, int n) {
    return total / n;
}

// String-free but included to show a function returning a single char based on logic
char calculateGrade(float average) {
    if (average >= 90) return 'A';
    else if (average >= 75) return 'B';
    else if (average >= 60) return 'C';
    else if (average >= 40) return 'D';
    else return 'F';
}

// Converts a string to uppercase in-place; demonstrates string + array-of-char handling
void toUpperCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void displayHeader() {
    printf("\n%-8s %-20s %-8s %-8s %-6s\n", "Roll No", "Name", "Total", "Average", "Grade");
    printf("--------------------------------------------------------\n");
}

void displayStudent(int roll, char name[], float marks[], float total, float avg, char grade) {
    printf("%-8d %-20s %-8.2f %-8.2f %-6c\n", roll, name, total, avg, grade);
}

void displayAll(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count) {
    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    displayHeader();
    for (int i = 0; i < count; i++) {
        float total = calculateTotal(marks[i], NUM_SUBJECTS);
        float avg = calculateAverage(total, NUM_SUBJECTS);
        char grade = calculateGrade(avg);
        displayStudent(rollNo[i], names[i], marks[i], total, avg, grade);
    }
}

// Returns the index of a matching roll number, or -1 if not found
int linearSearchByRoll(int rollNo[], int count, int key) {
    for (int i = 0; i < count; i++) {
        if (rollNo[i] == key) {
            return i;
        }
    }
    return -1;
}

void searchStudent(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count) {
    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    int key;
    printf("Enter Roll Number to search: ");
    scanf("%d", &key);

    int index = linearSearchByRoll(rollNo, count, key);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", key);
        return;
    }

    float total = calculateTotal(marks[index], NUM_SUBJECTS);
    float avg = calculateAverage(total, NUM_SUBJECTS);
    char grade = calculateGrade(avg);

    char displayName[NAME_LEN];
    strcpy(displayName, names[index]);
    toUpperCase(displayName); // demonstrate string function usage

    printf("\n--- Student Found ---\n");
    printf("Roll No : %d\n", rollNo[index]);
    printf("Name    : %s\n", displayName);
    for (int j = 0; j < NUM_SUBJECTS; j++) {
        printf("Subject %d Marks: %.2f\n", j + 1, marks[index][j]);
    }
    printf("Total   : %.2f\n", total);
    printf("Average : %.2f\n", avg);
    printf("Grade   : %c\n", grade);
}

// Bubble sort by average descending; swaps across all parallel arrays together
void sortByAverage(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            float avgJ = calculateAverage(calculateTotal(marks[j], NUM_SUBJECTS), NUM_SUBJECTS);
            float avgJ1 = calculateAverage(calculateTotal(marks[j + 1], NUM_SUBJECTS), NUM_SUBJECTS);

            if (avgJ < avgJ1) {
                // Swap roll numbers
                int tempRoll = rollNo[j];
                rollNo[j] = rollNo[j + 1];
                rollNo[j + 1] = tempRoll;

                // Swap names
                char tempName[NAME_LEN];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                // Swap marks array (all subjects)
                for (int k = 0; k < NUM_SUBJECTS; k++) {
                    float tempMark = marks[j][k];
                    marks[j][k] = marks[j + 1][k];
                    marks[j + 1][k] = tempMark;
                }
            }
        }
    }
}

void classStatistics(char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count) {
    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    float classTotal = 0, highestAvg = -1, lowestAvg = 101;
    int highestIndex = 0, lowestIndex = 0;

    for (int i = 0; i < count; i++) {
        float total = calculateTotal(marks[i], NUM_SUBJECTS);
        float avg = calculateAverage(total, NUM_SUBJECTS);

        classTotal += avg;

        if (avg > highestAvg) {
            highestAvg = avg;
            highestIndex = i;
        }
        if (avg < lowestAvg) {
            lowestAvg = avg;
            lowestIndex = i;
        }
    }

    printf("\n--- Class Statistics ---\n");
    printf("Total Students   : %d\n", count);
    printf("Class Average    : %.2f\n", classTotal / count);
    printf("Highest Average  : %.2f (%s)\n", highestAvg, names[highestIndex]);
    printf("Lowest Average   : %.2f (%s)\n", lowestAvg, names[lowestIndex]);
}

void findTopper(int rollNo[], char names[][NAME_LEN], float marks[][NUM_SUBJECTS], int count) {
    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    int topIndex = 0;
    float topAvg = calculateAverage(calculateTotal(marks[0], NUM_SUBJECTS), NUM_SUBJECTS);

    for (int i = 1; i < count; i++) {
        float avg = calculateAverage(calculateTotal(marks[i], NUM_SUBJECTS), NUM_SUBJECTS);
        if (avg > topAvg) {
            topAvg = avg;
            topIndex = i;
        }
    }

    char grade = calculateGrade(topAvg);

    printf("\n--- Class Topper ---\n");
    printf("Roll No : %d\n", rollNo[topIndex]);
    printf("Name    : %s\n", names[topIndex]);
    printf("Average : %.2f\n", topAvg);
    printf("Grade   : %c\n", grade);
}