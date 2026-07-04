/*Write a program to Create contact
management system.
*/

#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact {
    int contactId;
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
    int isActive;
};

struct Contact contacts[MAX_CONTACTS];
int contactCount = 0;
int nextContactId = 1;

// ---------- Lookup helpers ----------

int findContactIndex(int contactId) {
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].isActive && contacts[i].contactId == contactId) {
            return i;
        }
    }
    return -1;
}

int phoneExists(char *phone) {
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].isActive && strcmp(contacts[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}

// ---------- Core operations ----------

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }

    struct Contact c;
    c.contactId = nextContactId;
    getchar();

    printf("Enter Name: ");
    fgets(c.name, 50, stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(c.phone, 15, stdin);
    c.phone[strcspn(c.phone, "\n")] = '\0';

    if (phoneExists(c.phone)) {
        printf("Error: A contact with phone number %s already exists.\n", c.phone);
        return;
    }

    printf("Enter Email: ");
    fgets(c.email, 50, stdin);
    c.email[strcspn(c.email, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(c.address, 100, stdin);
    c.address[strcspn(c.address, "\n")] = '\0';

    c.isActive = 1;
    contacts[contactCount++] = c;
    nextContactId++;

    printf("Contact added successfully! Contact ID: %d\n", c.contactId);
}

void displayAll() {
    int found = 0;
    printf("\n%-6s %-20s %-15s %-25s\n", "ID", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].isActive) {
            printf("%-6d %-20s %-15s %-25s\n",
                   contacts[i].contactId, contacts[i].name,
                   contacts[i].phone, contacts[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts found.\n");
    }
}

void viewContact(int index) {
    printf("\n--- Contact Details ---\n");
    printf("ID      : %d\n", contacts[index].contactId);
    printf("Name    : %s\n", contacts[index].name);
    printf("Phone   : %s\n", contacts[index].phone);
    printf("Email   : %s\n", contacts[index].email);
    printf("Address : %s\n", contacts[index].address);
}

void searchByName() {
    char keyword[50];
    getchar();
    printf("Enter name keyword to search: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\nSearch Results:\n");
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].isActive && strstr(contacts[i].name, keyword) != NULL) {
            printf("ID: %d | Name: %s | Phone: %s\n",
                   contacts[i].contactId, contacts[i].name, contacts[i].phone);
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts matched your search.\n");
    }
}

void searchById() {
    int contactId;
    printf("Enter Contact ID: ");
    scanf("%d", &contactId);

    int index = findContactIndex(contactId);
    if (index == -1) {
        printf("Contact ID %d not found.\n", contactId);
        return;
    }

    viewContact(index);
}

void updateContact() {
    int contactId;
    printf("Enter Contact ID to update: ");
    scanf("%d", &contactId);

    int index = findContactIndex(contactId);
    if (index == -1) {
        printf("Contact ID %d not found.\n", contactId);
        return;
    }

    getchar();

    printf("Enter new Name: ");
    fgets(contacts[index].name, 50, stdin);
    contacts[index].name[strcspn(contacts[index].name, "\n")] = '\0';

    printf("Enter new Phone Number: ");
    fgets(contacts[index].phone, 15, stdin);
    contacts[index].phone[strcspn(contacts[index].phone, "\n")] = '\0';

    printf("Enter new Email: ");
    fgets(contacts[index].email, 50, stdin);
    contacts[index].email[strcspn(contacts[index].email, "\n")] = '\0';

    printf("Enter new Address: ");
    fgets(contacts[index].address, 100, stdin);
    contacts[index].address[strcspn(contacts[index].address, "\n")] = '\0';

    printf("Contact updated successfully!\n");
}

void deleteContact() {
    int contactId;
    printf("Enter Contact ID to delete: ");
    scanf("%d", &contactId);

    int index = findContactIndex(contactId);
    if (index == -1) {
        printf("Contact ID %d not found.\n", contactId);
        return;
    }

    contacts[index].isActive = 0;
    printf("Contact deleted successfully!\n");
}

// Simple bubble sort by name (alphabetical)
void sortByName() {
    struct Contact temp;
    int n = contactCount;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (contacts[j].isActive && contacts[j + 1].isActive &&
                strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }

    printf("Contacts sorted alphabetically by name.\n");
    displayAll();
}

int main() {
    int choice;

    do {
        printf("\n===== CONTACT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Update Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Sort by Name\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayAll(); break;
            case 3: searchById(); break;
            case 4: searchByName(); break;
            case 5: updateContact(); break;
            case 6: deleteContact(); break;
            case 7: sortByName(); break;
            case 8: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}