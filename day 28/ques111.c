// Write a program to Create ticket booking system 

#include <stdio.h>
#include <string.h>

#define MAX_SHOWS 20
#define MAX_SEATS 50
#define TICKET_PRICE 200.0

struct Show {
    int showId;
    char movieName[50];
    char showTime[20];
    int totalSeats;
    int seats[MAX_SEATS]; // 0 = available, 1 = booked
    int isActive;
};

struct Booking {
    int bookingId;
    int showId;
    char passengerName[50];
    int seatNo;
    float amountPaid;
    int isCancelled;
};

struct Show shows[MAX_SHOWS];
struct Booking bookings[500];
int showCount = 0;
int bookingCount = 0;
int nextBookingId = 1;

// ---------- Lookup helpers ----------

int findShowIndex(int showId) {
    for (int i = 0; i < showCount; i++) {
        if (shows[i].isActive && shows[i].showId == showId) {
            return i;
        }
    }
    return -1;
}

int showIdExists(int showId) {
    return findShowIndex(showId) != -1;
}

// ---------- Show management ----------

void addShow() {
    if (showCount >= MAX_SHOWS) {
        printf("Show list is full!\n");
        return;
    }

    struct Show s;
    printf("Enter Show ID: ");
    scanf("%d", &s.showId);

    if (showIdExists(s.showId)) {
        printf("Error: Show ID %d already exists.\n", s.showId);
        return;
    }
    getchar();

    printf("Enter Movie Name: ");
    fgets(s.movieName, 50, stdin);
    s.movieName[strcspn(s.movieName, "\n")] = '\0';

    printf("Enter Show Time (e.g. 6:00 PM): ");
    fgets(s.showTime, 20, stdin);
    s.showTime[strcspn(s.showTime, "\n")] = '\0';

    printf("Enter Total Seats (max %d): ", MAX_SEATS);
    scanf("%d", &s.totalSeats);

    if (s.totalSeats > MAX_SEATS) {
        s.totalSeats = MAX_SEATS;
        printf("Capped to maximum of %d seats.\n", MAX_SEATS);
    }

    for (int i = 0; i < s.totalSeats; i++) {
        s.seats[i] = 0; // all seats available initially
    }

    s.isActive = 1;
    shows[showCount++] = s;

    printf("Show added successfully! Show ID: %d\n", s.showId);
}

void displayShows() {
    int found = 0;
    printf("\n%-6s %-25s %-12s %-10s %-10s\n", "ID", "Movie", "Time", "Total", "Available");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < showCount; i++) {
        if (shows[i].isActive) {
            int available = 0;
            for (int j = 0; j < shows[i].totalSeats; j++) {
                if (shows[i].seats[j] == 0) available++;
            }

            printf("%-6d %-25s %-12s %-10d %-10d\n",
                   shows[i].showId, shows[i].movieName, shows[i].showTime,
                   shows[i].totalSeats, available);
            found = 1;
        }
    }

    if (!found) {
        printf("No shows available.\n");
    }
}

void viewSeatMap(int index) {
    printf("\nSeat Map for \"%s\" (%s):\n", shows[index].movieName, shows[index].showTime);
    for (int i = 0; i < shows[index].totalSeats; i++) {
        printf("[%2d:%s] ", i + 1, shows[index].seats[i] == 0 ? "O" : "X");
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n(O = Available, X = Booked)\n");
}

// ---------- Booking operations ----------

void bookTicket() {
    int showId;
    printf("Enter Show ID: ");
    scanf("%d", &showId);

    int sIndex = findShowIndex(showId);
    if (sIndex == -1) {
        printf("Show ID %d not found.\n", showId);
        return;
    }

    viewSeatMap(sIndex);

    int seatNo;
    printf("Enter Seat Number to book: ");
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > shows[sIndex].totalSeats) {
        printf("Invalid seat number.\n");
        return;
    }

    if (shows[sIndex].seats[seatNo - 1] == 1) {
        printf("Seat %d is already booked. Please choose another.\n", seatNo);
        return;
    }

    struct Booking b;
    b.bookingId = nextBookingId++;
    b.showId = showId;
    getchar();

    printf("Enter Passenger Name: ");
    fgets(b.passengerName, 50, stdin);
    b.passengerName[strcspn(b.passengerName, "\n")] = '\0';

    b.seatNo = seatNo;
    b.amountPaid = TICKET_PRICE;
    b.isCancelled = 0;

    bookings[bookingCount++] = b;
    shows[sIndex].seats[seatNo - 1] = 1;

    printf("\n=== BOOKING CONFIRMED ===\n");
    printf("Booking ID : %d\n", b.bookingId);
    printf("Movie      : %s\n", shows[sIndex].movieName);
    printf("Show Time  : %s\n", shows[sIndex].showTime);
    printf("Seat No    : %d\n", b.seatNo);
    printf("Passenger  : %s\n", b.passengerName);
    printf("Amount Paid: %.2f\n", b.amountPaid);
    printf("=========================\n");
}

int findBookingIndex(int bookingId) {
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingId == bookingId && !bookings[i].isCancelled) {
            return i;
        }
    }
    return -1;
}

void cancelBooking() {
    int bookingId;
    printf("Enter Booking ID to cancel: ");
    scanf("%d", &bookingId);

    int bIndex = findBookingIndex(bookingId);
    if (bIndex == -1) {
        printf("Booking ID %d not found or already cancelled.\n", bookingId);
        return;
    }

    int sIndex = findShowIndex(bookings[bIndex].showId);
    if (sIndex != -1) {
        shows[sIndex].seats[bookings[bIndex].seatNo - 1] = 0; // free up the seat
    }

    bookings[bIndex].isCancelled = 1;

    printf("Booking %d cancelled successfully. Seat %d is now available.\n",
           bookingId, bookings[bIndex].seatNo);
    printf("Refund amount: %.2f\n", bookings[bIndex].amountPaid);
}

void viewBooking() {
    int bookingId;
    printf("Enter Booking ID: ");
    scanf("%d", &bookingId);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingId == bookingId) {
            int sIndex = findShowIndex(bookings[i].showId);

            printf("\n--- Booking Details ---\n");
            printf("Booking ID : %d\n", bookings[i].bookingId);
            printf("Movie      : %s\n", sIndex != -1 ? shows[sIndex].movieName : "N/A");
            printf("Seat No    : %d\n", bookings[i].seatNo);
            printf("Passenger  : %s\n", bookings[i].passengerName);
            printf("Amount Paid: %.2f\n", bookings[i].amountPaid);
            printf("Status     : %s\n", bookings[i].isCancelled ? "CANCELLED" : "CONFIRMED");
            return;
        }
    }

    printf("Booking ID %d not found.\n", bookingId);
}

void showRevenue() {
    float total = 0;
    int confirmedCount = 0;

    for (int i = 0; i < bookingCount; i++) {
        if (!bookings[i].isCancelled) {
            total += bookings[i].amountPaid;
            confirmedCount++;
        }
    }

    printf("\n--- Revenue Report ---\n");
    printf("Confirmed Bookings : %d\n", confirmedCount);
    printf("Total Revenue      : %.2f\n", total);
}

int main() {
    int choice;

    do {
        printf("\n===== TICKET BOOKING SYSTEM =====\n");
        printf("1. Add Show\n");
        printf("2. Display All Shows\n");
        printf("3. Book Ticket\n");
        printf("4. Cancel Booking\n");
        printf("5. View Booking Details\n");
        printf("6. Revenue Report\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addShow(); break;
            case 2: displayShows(); break;
            case 3: bookTicket(); break;
            case 4: cancelBooking(); break;
            case 5: viewBooking(); break;
            case 6: showRevenue(); break;
            case 7: printf("Thank you for using the booking system. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}