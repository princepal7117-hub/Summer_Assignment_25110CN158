/*Write a program to Create employee
management system*/

#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int empId;
    char name[50];
    char department[30];
    float salary;
    int isActive; // 1 = record in use, 0 = deleted/empty slot
};

struct Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Check if an employee ID already exists (to prevent duplicates)
int idExists(int empId) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].isActive && employees[i].empId == empId) {
            return 1;
        }
    }
    return 0;
}

// Add a new employee record
void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }

    struct Employee e;
    printf("Enter Employee ID: ");
    scanf("%d", &e.empId);

    if (idExists(e.empId)) {
        printf("Error: Employee ID %d already exists.\n", e.empId);
        return;
    }
    getchar();

    printf("Enter Name: ");
    fgets(e.name, 50, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(e.department, 30, stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    e.isActive = 1;
    employees[employeeCount++] = e;

    printf("Employee record added successfully!\n");
}

// Display all employee records
void displayAll() {
    int found = 0;
    printf("\n%-8s %-20s %-15s %-10s\n", "ID", "Name", "Department", "Salary");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].isActive) {
            printf("%-8d %-20s %-15s %-10.2f\n",
                   employees[i].empId, employees[i].name,
                   employees[i].department, employees[i].salary);
            found = 1;
        }
    }

    if (!found) {
        printf("No employee records found.\n");
    }
}

// Search for an employee by ID
int findEmployeeIndex(int empId) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].isActive && employees[i].empId == empId) {
            return i;
        }
    }
    return -1;
}

void searchEmployee() {
    int empId;
    printf("Enter Employee ID to search: ");
    scanf("%d", &empId);

    int index = findEmployeeIndex(empId);

    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
    } else {
        printf("\n--- Employee Found ---\n");
        printf("ID        : %d\n", employees[index].empId);
        printf("Name      : %s\n", employees[index].name);
        printf("Department: %s\n", employees[index].department);
        printf("Salary    : %.2f\n", employees[index].salary);
    }
}

// Update an existing employee's details
void updateEmployee() {
    int empId;
    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    int index = findEmployeeIndex(empId);

    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
        return;
    }

    getchar(); // consume leftover newline

    printf("Enter new Name: ");
    fgets(employees[index].name, 50, stdin);
    employees[index].name[strcspn(employees[index].name, "\n")] = '\0';

    printf("Enter new Department: ");
    fgets(employees[index].department, 30, stdin);
    employees[index].department[strcspn(employees[index].department, "\n")] = '\0';

    printf("Enter new Salary: ");
    scanf("%f", &employees[index].salary);

    printf("Employee record updated successfully!\n");
}

// Delete an employee record (soft delete using isActive flag)
void deleteEmployee() {
    int empId;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &empId);

    int index = findEmployeeIndex(empId);

    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
        return;
    }

    employees[index].isActive = 0;
    printf("Employee record deleted successfully!\n");
}

// Display total and average salary across all active employees
void salaryReport() {
    float total = 0;
    int count = 0;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].isActive) {
            total += employees[i].salary;
            count++;
        }
    }

    if (count == 0) {
        printf("No active employees to report on.\n");
        return;
    }

    printf("\n--- Salary Report ---\n");
    printf("Total Employees : %d\n", count);
    printf("Total Payroll    : %.2f\n", total);
    printf("Average Salary   : %.2f\n", total / count);
}

int main() {
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Salary Report\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: salaryReport(); break;
            case 7: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}