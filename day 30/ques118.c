/*Write a program to Create mini library
system*/

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50

struct Book {
    int id;
    char title[50];
    char author[40];
    int isIssued; // 0 = available, 1 = issued
};

struct Book books[MAX_BOOKS];
int bookCount = 0;
int nextId = 1;

// ---------- Lookup helper ----------

int findBook(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------- Core operations ----------

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }

    struct Book b;
    b.id = nextId++;
    getchar();

    printf("Enter Title: ");
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(b.author, 40, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    b.isIssued = 0;
    books[bookCount++] = b;

    printf("Book added! ID: %d\n", b.id);
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n%-5s %-25s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-25s %-20s %-10s\n",
               books[i].id, books[i].title, books[i].author,
               books[i].isIssued ? "Issued" : "Available");
    }
}

void issueBook() {
    int id;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    int index = findBook(id);

    if (index == -1) {
        printf("Book ID %d not found.\n", id);
    } else if (books[index].isIssued) {
        printf("\"%s\" is already issued.\n", books[index].title);
    } else {
        books[index].isIssued = 1;
        printf("\"%s\" issued successfully.\n", books[index].title);
    }
}

void returnBook() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    int index = findBook(id);

    if (index == -1) {
        printf("Book ID %d not found.\n", id);
    } else if (!books[index].isIssued) {
        printf("\"%s\" was not issued.\n", books[index].title);
    } else {
        books[index].isIssued = 0;
        printf("\"%s\" returned successfully.\n", books[index].title);
    }
}

void searchBook() {
    char keyword[50];
    getchar();
    printf("Enter title keyword: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL) {
            printf("ID: %d | %s by %s | %s\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].isIssued ? "Issued" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No matching books found.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== MINI LIBRARY SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: searchBook(); break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}