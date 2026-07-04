//Write a program to Create salary management system 

#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define HRA_PERCENT 0.20
#define DA_PERCENT 0.15
#define PF_PERCENT 0.12
#define PROFESSIONAL_TAX 200.0

struct Salary {
    int empId;
    char name[50];
    float basicSalary;
    float hra;
    float da;
    float pf;
    float tax;
    float grossSalary;
    float netSalary;
    int isActive;
};

struct Salary records[MAX_EMPLOYEES];
int recordCount = 0;

// Calculate income tax based on annual gross salary (simplified slabs)
float calculateTax(float annualGross) {
    float tax = 0;

    if (annualGross <= 250000) {
        tax = 0;
    } else if (annualGross <= 500000) {
        tax = (annualGross - 250000) * 0.05;
    } else if (annualGross <= 1000000) {
        tax = 12500 + (annualGross - 500000) * 0.20;
    } else {
        tax = 112500 + (annualGross - 1000000) * 0.30;
    }

    return tax / 12; // convert annual tax to monthly
}

// Compute all salary components based on basic salary
void computeSalary(struct Salary *s) {
    s->hra = s->basicSalary * HRA_PERCENT;
    s->da = s->basicSalary * DA_PERCENT;
    s->pf = s->basicSalary * PF_PERCENT;

    s->grossSalary = s->basicSalary + s->hra + s->da;

    float annualGross = s->grossSalary * 12;
    s->tax = calculateTax(annualGross);

    s->netSalary = s->grossSalary - s->pf - s->tax - PROFESSIONAL_TAX;
}

int idExists(int empId) {
    for (int i = 0; i < recordCount; i++) {
        if (records[i].isActive && records[i].empId == empId) {
            return 1;
        }
    }
    return 0;
}

int findIndex(int empId) {
    for (int i = 0; i < recordCount; i++) {
        if (records[i].isActive && records[i].empId == empId) {
            return i;
        }
    }
    return -1;
}

void addSalaryRecord() {
    if (recordCount >= MAX_EMPLOYEES) {
        printf("Salary records are full!\n");
        return;
    }

    struct Salary s;
    printf("Enter Employee ID: ");
    scanf("%d", &s.empId);

    if (idExists(s.empId)) {
        printf("Error: Employee ID %d already exists.\n", s.empId);
        return;
    }
    getchar();

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Basic Salary: ");
    scanf("%f", &s.basicSalary);

    computeSalary(&s);
    s.isActive = 1;
    records[recordCount++] = s;

    printf("Salary record added and computed successfully!\n");
}

void displaySlip(struct Salary s) {
    printf("\n========== SALARY SLIP ==========\n");
    printf("Employee ID     : %d\n", s.empId);
    printf("Name            : %s\n", s.name);
    printf("----------------------------------\n");
    printf("Basic Salary    : %10.2f\n", s.basicSalary);
    printf("HRA (20%%)       : %10.2f\n", s.hra);
    printf("DA (15%%)        : %10.2f\n", s.da);
    printf("Gross Salary    : %10.2f\n", s.grossSalary);
    printf("----------------------------------\n");
    printf("PF Deduction    : %10.2f\n", s.pf);
    printf("Income Tax      : %10.2f\n", s.tax);
    printf("Professional Tax: %10.2f\n", PROFESSIONAL_TAX);
    printf("----------------------------------\n");
    printf("NET SALARY      : %10.2f\n", s.netSalary);
    printf("==================================\n");
}

void viewSlip() {
    int empId;
    printf("Enter Employee ID: ");
    scanf("%d", &empId);

    int index = findIndex(empId);
    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
        return;
    }

    displaySlip(records[index]);
}

void displayAll() {
    int found = 0;
    printf("\n%-6s %-18s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Basic", "Gross", "Tax", "Net");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < recordCount; i++) {
        if (records[i].isActive) {
            printf("%-6d %-18s %-10.2f %-10.2f %-10.2f %-10.2f\n",
                   records[i].empId, records[i].name,
                   records[i].basicSalary, records[i].grossSalary,
                   records[i].tax, records[i].netSalary);
            found = 1;
        }
    }

    if (!found) {
        printf("No salary records found.\n");
    }
}

void updateBasicSalary() {
    int empId;
    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    int index = findIndex(empId);
    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
        return;
    }

    printf("Enter new Basic Salary: ");
    scanf("%f", &records[index].basicSalary);

    computeSalary(&records[index]);
    printf("Salary updated and recalculated successfully!\n");
}

void deleteRecord() {
    int empId;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &empId);

    int index = findIndex(empId);
    if (index == -1) {
        printf("Employee with ID %d not found.\n", empId);
        return;
    }

    records[index].isActive = 0;
    printf("Salary record deleted successfully!\n");
}

void payrollSummary() {
    float totalGross = 0, totalNet = 0, totalTax = 0, totalPF = 0;
    int count = 0;

    for (int i = 0; i < recordCount; i++) {
        if (records[i].isActive) {
            totalGross += records[i].grossSalary;
            totalNet += records[i].netSalary;
            totalTax += records[i].tax;
            totalPF += records[i].pf;
            count++;
        }
    }

    if (count == 0) {
        printf("No active employees for payroll summary.\n");
        return;
    }

    printf("\n--- Monthly Payroll Summary ---\n");
    printf("Total Employees      : %d\n", count);
    printf("Total Gross Payroll  : %.2f\n", totalGross);
    printf("Total Tax Deducted   : %.2f\n", totalTax);
    printf("Total PF Deducted    : %.2f\n", totalPF);
    printf("Total Net Payroll    : %.2f\n", totalNet);
}

int main() {
    int choice;

    do {
        printf("\n===== SALARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee Salary Record\n");
        printf("2. View Salary Slip\n");
        printf("3. Display All Records\n");
        printf("4. Update Basic Salary\n");
        printf("5. Delete Record\n");
        printf("6. Payroll Summary\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSalaryRecord(); break;
            case 2: viewSlip(); break;
            case 3: displayAll(); break;
            case 4: updateBasicSalary(); break;
            case 5: deleteRecord(); break;
            case 6: payrollSummary(); break;
            case 7: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}