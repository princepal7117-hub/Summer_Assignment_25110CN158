// Write a program to Create marksheet generation system 

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NUM_SUBJECTS 5
#define MAX_MARKS_PER_SUBJECT 100

struct Student {
    int rollNo;
    char name[50];
    char subjectNames[NUM_SUBJECTS][20];
    float marks[NUM_SUBJECTS];
    float total;
    float percentage;
    char grade;
    int isActive;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Determine grade based on percentage
char calculateGrade(float percentage) {
    if (percentage >= 90) return 'A';
    else if (percentage >= 75) return 'B';
    else if (percentage >= 60) return 'C';
    else if (percentage >= 40) return 'D';
    else return 'F';
}

// Check if a student has failed (any subject below 33, common passing criteria)
int hasFailed(struct Student *s) {
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (s->marks[i] < 33) {
            return 1;
        }
    }
    return 0;
}

int idExists(int rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNo == rollNo) {
            return 1;
        }
    }
    return 0;
}

int findIndex(int rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNo == rollNo) {
            return i;
        }
    }
    return -1;
}

// Compute total, percentage, and grade for a student
void computeResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        s->total += s->marks[i];
    }
    s->percentage = s->total / NUM_SUBJECTS;
    s->grade = calculateGrade(s->percentage);
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student records are full!\n");
        return;
    }

    struct Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    if (idExists(s.rollNo)) {
        printf("Error: Roll Number %d already exists.\n", s.rollNo);
        return;
    }
    getchar();

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter marks for %d subjects (out of %d each):\n", NUM_SUBJECTS, MAX_MARKS_PER_SUBJECT);
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter name of Subject %d: ", i + 1);
        fgets(s.subjectNames[i], 20, stdin);
        s.subjectNames[i][strcspn(s.subjectNames[i], "\n")] = '\0';

        float mark;
        do {
            printf("Enter marks in %s (0-%d): ", s.subjectNames[i], MAX_MARKS_PER_SUBJECT);
            scanf("%f", &mark);
            if (mark < 0 || mark > MAX_MARKS_PER_SUBJECT) {
                printf("Invalid marks! Please enter between 0 and %d.\n", MAX_MARKS_PER_SUBJECT);
            }
        } while (mark < 0 || mark > MAX_MARKS_PER_SUBJECT);

        s.marks[i] = mark;
        getchar(); // consume leftover newline before next fgets
    }

    computeResult(&s);
    s.isActive = 1;
    students[studentCount++] = s;

    printf("Student record added and result computed successfully!\n");
}

void printMarksheet(struct Student s) {
    printf("\n============ MARKSHEET ============\n");
    printf("Roll No : %d\n", s.rollNo);
    printf("Name    : %s\n", s.name);
    printf("------------------------------------\n");
    printf("%-20s %-10s\n", "Subject", "Marks");
    printf("------------------------------------\n");

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%-20s %-10.2f\n", s.subjectNames[i], s.marks[i]);
    }

    printf("------------------------------------\n");
    printf("Total Marks   : %.2f / %d\n", s.total, NUM_SUBJECTS * MAX_MARKS_PER_SUBJECT);
    printf("Percentage    : %.2f%%\n", s.percentage);
    printf("Grade         : %c\n", s.grade);
    printf("Result        : %s\n", hasFailed(&s) ? "FAIL" : "PASS");
    printf("====================================\n");
}

void viewMarksheet() {
    int rollNo;
    printf("Enter Roll Number: ");
    scanf("%d", &rollNo);

    int index = findIndex(rollNo);
    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    printMarksheet(students[index]);
}

void displayAll() {
    int found = 0;
    printf("\n%-8s %-20s %-10s %-12s %-6s %-6s\n",
           "Roll No", "Name", "Total", "Percentage", "Grade", "Result");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            printf("%-8d %-20s %-10.2f %-12.2f %-6c %-6s\n",
                   students[i].rollNo, students[i].name,
                   students[i].total, students[i].percentage,
                   students[i].grade, hasFailed(&students[i]) ? "FAIL" : "PASS");
            found = 1;
        }
    }

    if (!found) {
        printf("No student records found.\n");
    }
}

void updateMarks() {
    int rollNo;
    printf("Enter Roll Number to update marks: ");
    scanf("%d", &rollNo);

    int index = findIndex(rollNo);
    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        float mark;
        do {
            printf("Enter new marks in %s (0-%d): ", students[index].subjectNames[i], MAX_MARKS_PER_SUBJECT);
            scanf("%f", &mark);
            if (mark < 0 || mark > MAX_MARKS_PER_SUBJECT) {
                printf("Invalid marks! Please enter between 0 and %d.\n", MAX_MARKS_PER_SUBJECT);
            }
        } while (mark < 0 || mark > MAX_MARKS_PER_SUBJECT);
        students[index].marks[i] = mark;
    }

    computeResult(&students[index]);
    printf("Marks updated and result recalculated successfully!\n");
}

void deleteStudent() {
    int rollNo;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNo);

    int index = findIndex(rollNo);
    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    students[index].isActive = 0;
    printf("Student record deleted successfully!\n");
}

void classTopper() {
    int found = 0, topIndex = -1;
    float highest = -1;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].percentage > highest) {
            highest = students[i].percentage;
            topIndex = i;
            found = 1;
        }
    }

    if (!found) {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Class Topper ---\n");
    printf("Roll No    : %d\n", students[topIndex].rollNo);
    printf("Name       : %s\n", students[topIndex].name);
    printf("Percentage : %.2f%%\n", students[topIndex].percentage);
    printf("Grade      : %c\n", students[topIndex].grade);
}

int main() {
    int choice;

    do {
        printf("\n===== MARKSHEET GENERATION SYSTEM =====\n");
        printf("1. Add Student & Enter Marks\n");
        printf("2. View Marksheet\n");
        printf("3. Display All Results\n");
        printf("4. Update Marks\n");
        printf("5. Delete Student\n");
        printf("6. Class Topper\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewMarksheet(); break;
            case 3: displayAll(); break;
            case 4: updateMarks(); break;
            case 5: deleteStudent(); break;
            case 6: classTopper(); break;
            case 7: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}