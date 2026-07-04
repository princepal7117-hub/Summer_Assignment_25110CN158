/*Write a program to Create student record
management system.*/

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNo;
    char name[50];
    int age;
    float marks;
    int isActive; // 1 = record in use, 0 = deleted/empty slot
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Add a new student record
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }

    struct Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);
    getchar();

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    s.isActive = 1;
    students[studentCount++] = s;

    printf("Student record added successfully!\n");
}

// Display all student records
void displayAll() {
    int found = 0;
    printf("\n%-10s %-20s %-6s %-8s\n", "Roll No", "Name", "Age", "Marks");
    printf("---------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            printf("%-10d %-20s %-6d %-8.2f\n",
                   students[i].rollNo, students[i].name,
                   students[i].age, students[i].marks);
            found = 1;
        }
    }

    if (!found) {
        printf("No student records found.\n");
    }
}

// Search for a student by roll number
int findStudentIndex(int rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNo == rollNo) {
            return i;
        }
    }
    return -1;
}

void searchStudent() {
    int rollNo;
    printf("Enter Roll Number to search: ");
    scanf("%d", &rollNo);

    int index = findStudentIndex(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
    } else {
        printf("\n--- Student Found ---\n");
        printf("Roll No: %d\n", students[index].rollNo);
        printf("Name   : %s\n", students[index].name);
        printf("Age    : %d\n", students[index].age);
        printf("Marks  : %.2f\n", students[index].marks);
    }
}

// Update an existing student's details
void updateStudent() {
    int rollNo;
    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNo);

    int index = findStudentIndex(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    getchar(); // consume leftover newline

    printf("Enter new Name: ");
    fgets(students[index].name, 50, stdin);
    students[index].name[strcspn(students[index].name, "\n")] = '\0';

    printf("Enter new Age: ");
    scanf("%d", &students[index].age);

    printf("Enter new Marks: ");
    scanf("%f", &students[index].marks);

    printf("Student record updated successfully!\n");
}

// Delete a student record (soft delete using isActive flag)
void deleteStudent() {
    int rollNo;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNo);

    int index = findStudentIndex(rollNo);

    if (index == -1) {
        printf("Student with Roll No %d not found.\n", rollNo);
        return;
    }

    students[index].isActive = 0;
    printf("Student record deleted successfully!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}