/*Write a program to Create mini employee
management system*/

#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 50

struct Employee {
    int id;
    char name[50];
    char department[30];
    float salary;
};

struct Employee employees[MAX_EMPLOYEES];
int empCount = 0;
int nextId = 1;

// ---------- Lookup helper ----------

int findEmployee(int id) {
    for (int i = 0; i < empCount; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------- Core operations ----------

void addEmployee() {
    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }

    struct Employee e;
    e.id = nextId++;
    getchar();

    printf("Enter Name: ");
    fgets(e.name, 50, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(e.department, 30, stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    employees[empCount++] = e;

    printf("Employee added! ID: %d\n", e.id);
}

void displayEmployees() {
    if (empCount == 0) {
        printf("No employees found.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < empCount; i++) {
        printf("%-5d %-20s %-15s %-10.2f\n",
               employees[i].id, employees[i].name,
               employees[i].department, employees[i].salary);
    }
}

void searchEmployee() {
    int id;
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee ID %d not found.\n", id);
    } else {
        printf("\n--- Employee Found ---\n");
        printf("ID        : %d\n", employees[index].id);
        printf("Name      : %s\n", employees[index].name);
        printf("Department: %s\n", employees[index].department);
        printf("Salary    : %.2f\n", employees[index].salary);
    }
}

void updateSalary() {
    int id;
    printf("Enter Employee ID to update salary: ");
    scanf("%d", &id);

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee ID %d not found.\n", id);
        return;
    }

    printf("Enter new Salary: ");
    scanf("%f", &employees[index].salary);

    printf("Salary updated successfully!\n");
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee ID %d not found.\n", id);
        return;
    }

    // Shift all subsequent elements left by one to fill the gap
    for (int i = index; i < empCount - 1; i++) {
        employees[i] = employees[i + 1];
    }

    empCount--;
    printf("Employee deleted successfully!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== MINI EMPLOYEE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Salary\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateSalary(); break;
            case 5: deleteEmployee(); break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}