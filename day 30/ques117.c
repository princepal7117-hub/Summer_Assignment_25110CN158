/*Write a program to Create student record
system using arrays and strings.*/

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NAME_LEN 50

// Parallel arrays to store student data
int rollNumbers[MAX_STUDENTS];
char names[MAX_STUDENTS][NAME_LEN];
int ages[MAX_STUDENTS];
float marks[MAX_STUDENTS];
int totalStudents = 0;

// ---------- Core operations ----------

void addStudent() {
    if (totalStudents >= MAX_STUDENTS) {
        printf("Student records are full!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &rollNumbers[totalStudents]);
    getchar(); // consume leftover newline

    printf("Enter Name: ");
    fgets(names[totalStudents], NAME_LEN, stdin);
    names[totalStudents][strcspn(names[totalStudents], "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &ages[totalStudents]);

    printf("Enter Marks: ");
    scanf("%f", &marks[totalStudents]);

    totalStudents++;
    printf("Student record added successfully!\n");
}

void displayAll() {
    if (totalStudents == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-6s %-8s\n", "Roll No", "Name", "Age", "Marks");
    printf("---------------------------------------------\n");

    for (int i = 0; i < totalStudents; i++) {
        printf("%-10d %-20s %-6d %-8.2f\n",
               rollNumbers[i], names[i], ages[i], marks[i]);
    }
}

// Returns the array index for a given roll number, or -1 if not found
int findStudent(int rollNo) {
    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == rollNo) {
            return i;
        }
    }
    return -1;
}

void searchByRollNo() {
    int rollNo;
    printf("Enter Roll Number to search: ");
    scanf("%d", &rollNo);

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
    } else {
        printf("\n--- Student Found ---\n");
        printf("Roll No: %d\n", rollNumbers[index]);
        printf("Name   : %s\n", names[index]);
        printf("Age    : %d\n", ages[index]);
        printf("Marks  : %.2f\n", marks[index]);
    }
}

void searchByName() {
    char keyword[NAME_LEN];
    getchar();
    printf("Enter name (or part of it) to search: ");
    fgets(keyword, NAME_LEN, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\nSearch Results:\n");

    for (int i = 0; i < totalStudents; i++) {
        if (strstr(names[i], keyword) != NULL) {
            printf("Roll No: %d | Name: %s | Marks: %.2f\n",
                   rollNumbers[i], names[i], marks[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No students matched your search.\n");
    }
}

void updateStudent() {
    int rollNo;
    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNo);

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    getchar();

    printf("Enter new Name: ");
    fgets(names[index], NAME_LEN, stdin);
    names[index][strcspn(names[index], "\n")] = '\0';

    printf("Enter new Age: ");
    scanf("%d", &ages[index]);

    printf("Enter new Marks: ");
    scanf("%f", &marks[index]);

    printf("Student record updated successfully!\n");
}

void deleteStudent() {
    int rollNo;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNo);

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    // Shift all subsequent elements left by one position (in all arrays)
    for (int i = index; i < totalStudents - 1; i++) {
        rollNumbers[i] = rollNumbers[i + 1];
        strcpy(names[i], names[i + 1]);
        ages[i] = ages[i + 1];
        marks[i] = marks[i + 1];
    }

    totalStudents--;
    printf("Student record deleted successfully!\n");
}

// Sort by name alphabetically (bubble sort, shifting all parallel arrays together)
void sortByName() {
    if (totalStudents == 0) {
        printf("No student records found.\n");
        return;
    }

    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = 0; j < totalStudents - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                // Swap names
                char tempName[NAME_LEN];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                // Swap corresponding roll number, age, and marks to keep records aligned
                int tempRoll = rollNumbers[j];
                rollNumbers[j] = rollNumbers[j + 1];
                rollNumbers[j + 1] = tempRoll;

                int tempAge = ages[j];
                ages[j] = ages[j + 1];
                ages[j + 1] = tempAge;

                float tempMarks = marks[j];
                marks[j] = marks[j + 1];
                marks[j + 1] = tempMarks;
            }
        }
    }

    printf("Students sorted alphabetically by name.\n");
    displayAll();
}

void classStatistics() {
    if (totalStudents == 0) {
        printf("No student records found.\n");
        return;
    }

    float total = 0, highest = marks[0], lowest = marks[0];
    int highestIndex = 0, lowestIndex = 0;

    for (int i = 0; i < totalStudents; i++) {
        total += marks[i];
        if (marks[i] > highest) {
            highest = marks[i];
            highestIndex = i;
        }
        if (marks[i] < lowest) {
            lowest = marks[i];
            lowestIndex = i;
        }
    }

    printf("\n--- Class Statistics ---\n");
    printf("Total Students : %d\n", totalStudents);
    printf("Average Marks  : %.2f\n", total / totalStudents);
    printf("Highest Marks  : %.2f (%s, Roll No %d)\n",
           highest, names[highestIndex], rollNumbers[highestIndex]);
    printf("Lowest Marks   : %.2f (%s, Roll No %d)\n",
           lowest, names[lowestIndex], rollNumbers[lowestIndex]);
}

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search by Roll Number\n");
        printf("4. Search by Name\n");
        printf("5. Update Student\n");
        printf("6. Delete Student\n");
        printf("7. Sort by Name\n");
        printf("8. Class Statistics\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchByRollNo(); break;
            case 4: searchByName(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7: sortByName(); break;
            case 8: classStatistics(); break;
            case 9: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}