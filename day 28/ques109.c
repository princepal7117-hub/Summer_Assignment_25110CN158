/*Write a program to Create library
management system.*/

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50
#define MAX_ISSUE_DAYS 14
#define FINE_PER_DAY 5.0

struct Book {
    int bookId;
    char title[50];
    char author[50];
    int totalCopies;
    int availableCopies;
    int isActive;
};

struct Member {
    int memberId;
    char name[50];
    int booksIssued;
    int isActive;
};

struct IssueRecord {
    int bookId;
    int memberId;
    int issueDay; // simplified: day number since program start, instead of real dates
    int isReturned;
};

struct Book books[MAX_BOOKS];
struct Member members[MAX_MEMBERS];
struct IssueRecord issues[MAX_BOOKS];

int bookCount = 0;
int memberCount = 0;
int issueCount = 0;
int currentDay = 0; // simple simulated "day counter" for due dates/fines

// ---------- Lookup helpers ----------

int findBookIndex(int bookId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].isActive && books[i].bookId == bookId) {
            return i;
        }
    }
    return -1;
}

int findMemberIndex(int memberId) {
    for (int i = 0; i < memberCount; i++) {
        if (members[i].isActive && members[i].memberId == memberId) {
            return i;
        }
    }
    return -1;
}

int bookIdExists(int bookId) {
    return findBookIndex(bookId) != -1;
}

int memberIdExists(int memberId) {
    return findMemberIndex(memberId) != -1;
}

// ---------- Book management ----------

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book database is full!\n");
        return;
    }

    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.bookId);

    if (bookIdExists(b.bookId)) {
        printf("Error: Book ID %d already exists.\n", b.bookId);
        return;
    }
    getchar();

    printf("Enter Title: ");
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Number of Copies: ");
    scanf("%d", &b.totalCopies);

    b.availableCopies = b.totalCopies;
    b.isActive = 1;
    books[bookCount++] = b;

    printf("Book added successfully!\n");
}

void displayBooks() {
    int found = 0;
    printf("\n%-6s %-25s %-20s %-8s %-10s\n", "ID", "Title", "Author", "Total", "Available");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        if (books[i].isActive) {
            printf("%-6d %-25s %-20s %-8d %-10d\n",
                   books[i].bookId, books[i].title, books[i].author,
                   books[i].totalCopies, books[i].availableCopies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found.\n");
    }
}

void searchBook() {
    char keyword[50];
    getchar();
    printf("Enter title keyword to search: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\nSearch Results:\n");
    for (int i = 0; i < bookCount; i++) {
        if (books[i].isActive && strstr(books[i].title, keyword) != NULL) {
            printf("ID: %d | Title: %s | Author: %s | Available: %d\n",
                   books[i].bookId, books[i].title, books[i].author, books[i].availableCopies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books matched your search.\n");
    }
}

// ---------- Member management ----------

void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Member database is full!\n");
        return;
    }

    struct Member m;
    printf("Enter Member ID: ");
    scanf("%d", &m.memberId);

    if (memberIdExists(m.memberId)) {
        printf("Error: Member ID %d already exists.\n", m.memberId);
        return;
    }
    getchar();

    printf("Enter Name: ");
    fgets(m.name, 50, stdin);
    m.name[strcspn(m.name, "\n")] = '\0';

    m.booksIssued = 0;
    m.isActive = 1;
    members[memberCount++] = m;

    printf("Member registered successfully!\n");
}

void displayMembers() {
    int found = 0;
    printf("\n%-10s %-25s %-15s\n", "ID", "Name", "Books Issued");
    printf("--------------------------------------------\n");

    for (int i = 0; i < memberCount; i++) {
        if (members[i].isActive) {
            printf("%-10d %-25s %-15d\n", members[i].memberId, members[i].name, members[i].booksIssued);
            found = 1;
        }
    }

    if (!found) {
        printf("No members found.\n");
    }
}

// ---------- Issue / Return ----------

void issueBook() {
    int bookId, memberId;

    printf("Enter Book ID to issue: ");
    scanf("%d", &bookId);
    printf("Enter Member ID: ");
    scanf("%d", &memberId);

    int bIndex = findBookIndex(bookId);
    int mIndex = findMemberIndex(memberId);

    if (bIndex == -1) {
        printf("Book ID %d not found.\n", bookId);
        return;
    }
    if (mIndex == -1) {
        printf("Member ID %d not found.\n", memberId);
        return;
    }
    if (books[bIndex].availableCopies <= 0) {
        printf("No copies of \"%s\" currently available.\n", books[bIndex].title);
        return;
    }
    if (members[mIndex].booksIssued >= 3) {
        printf("Member has already issued the maximum allowed books (3).\n");
        return;
    }

    struct IssueRecord rec;
    rec.bookId = bookId;
    rec.memberId = memberId;
    rec.issueDay = currentDay;
    rec.isReturned = 0;
    issues[issueCount++] = rec;

    books[bIndex].availableCopies--;
    members[mIndex].booksIssued++;

    printf("Book \"%s\" issued to %s successfully. Due in %d days.\n",
           books[bIndex].title, members[mIndex].name, MAX_ISSUE_DAYS);
}

void returnBook() {
    int bookId, memberId;

    printf("Enter Book ID to return: ");
    scanf("%d", &bookId);
    printf("Enter Member ID: ");
    scanf("%d", &memberId);

    int recIndex = -1;
    for (int i = 0; i < issueCount; i++) {
        if (issues[i].bookId == bookId && issues[i].memberId == memberId && !issues[i].isReturned) {
            recIndex = i;
            break;
        }
    }

    if (recIndex == -1) {
        printf("No matching active issue record found.\n");
        return;
    }

    int bIndex = findBookIndex(bookId);
    int mIndex = findMemberIndex(memberId);

    int daysHeld = currentDay - issues[recIndex].issueDay;
    float fine = 0;

    if (daysHeld > MAX_ISSUE_DAYS) {
        fine = (daysHeld - MAX_ISSUE_DAYS) * FINE_PER_DAY;
    }

    issues[recIndex].isReturned = 1;
    books[bIndex].availableCopies++;
    members[mIndex].booksIssued--;

    printf("Book \"%s\" returned successfully.\n", books[bIndex].title);
    if (fine > 0) {
        printf("Book was overdue by %d day(s). Fine: %.2f\n", daysHeld - MAX_ISSUE_DAYS, fine);
    } else {
        printf("Returned on time. No fine.\n");
    }
}

void advanceDay() {
    int days;
    printf("Enter number of days to advance: ");
    scanf("%d", &days);
    currentDay += days;
    printf("Current day counter is now: %d\n", currentDay);
}

void viewIssuedBooks() {
    int found = 0;
    printf("\n%-8s %-8s %-10s %-8s\n", "BookID", "MemberID", "IssueDay", "Status");
    printf("-----------------------------------------\n");

    for (int i = 0; i < issueCount; i++) {
        if (!issues[i].isReturned) {
            printf("%-8d %-8d %-10d %-8s\n",
                   issues[i].bookId, issues[i].memberId, issues[i].issueDay, "ISSUED");
            found = 1;
        }
    }

    if (!found) {
        printf("No books are currently issued.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("Simulated Day: %d\n", currentDay);
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Register Member\n");
        printf("5. Display All Members\n");
        printf("6. Issue Book\n");
        printf("7. Return Book\n");
        printf("8. View Issued Books\n");
        printf("9. Advance Simulated Day (for testing fines)\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: addMember(); break;
            case 5: displayMembers(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: viewIssuedBooks(); break;
            case 9: advanceDay(); break;
            case 10: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 10);

    return 0;
}