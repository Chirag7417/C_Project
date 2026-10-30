#include <stdio.h>
#include <string.h>

#define TRAINS 3
#define SEATS 10
#define MAX 100

struct Train {
    int number;
    char name[30];
    char route[30];
    int fare;
};

struct Passenger {
    int id, age, train, seat;
    char name[30];
    char gender;
};

struct Train trains[TRAINS] = {
    {12951, "Rajdhani Express", "Jaipur-Delhi", 450},
    {12015, "Shatabdi Express", "Jaipur-Agra", 300},
    {12956, "Mumbai Superfast", "Jaipur-Mumbai", 900}
};

struct Passenger passengers[MAX];
int seats[TRAINS][SEATS] = {0};
int total = 0;
int nextId = 1001;


void showTrains() {
    int i;

    printf("\nAvailable Trains:\n");

    for (i = 0; i < TRAINS; i++) {
        printf("%d. %s | %s | Rs.%d\n",
               i + 1, trains[i].name,
               trains[i].route, trains[i].fare);
    }
}


void checkSeats() {
    int t, s;

    showTrains();
    printf("Enter train number (1-3): ");
    scanf("%d", &t);

    if (t < 1 || t > TRAINS) {
        printf("Invalid train number!\n");
        return;
    }

    printf("\nSeats of %s:\n", trains[t - 1].name);

    for (s = 0; s < SEATS; s++) {
        if (seats[t - 1][s] == 0)
            printf("[%d: Free] ", s + 1);
        else
            printf("[%d: Booked] ", s + 1);

        if ((s + 1) % 2 == 0)
            printf("\n");
    }
}


void bookTicket() {
    int t, s;

    if (total >= MAX) {
        printf("Booking list is full!\n");
        return;
    }

    showTrains();
    printf("Enter train number (1-3): ");
    scanf("%d", &t);

    if (t < 1 || t > TRAINS) {
        printf("Invalid train number!\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf(" %29[^\n]", passengers[total].name);

    printf("Enter age: ");
    scanf("%d", &passengers[total].age);

    printf("Enter gender (M/F): ");
    scanf(" %c", &passengers[total].gender);

    printf("Enter seat number (1-10): ");
    scanf("%d", &s);

    if (s < 1 || s > SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    if (seats[t - 1][s - 1] == 1) {
        printf("Seat already booked!\n");
        return;
    }

    seats[t - 1][s - 1] = 1;

    passengers[total].id = nextId;
    passengers[total].train = t;
    passengers[total].seat = s;

    printf("\n--- TICKET BOOKED ---\n");
    printf("Ticket ID: %d\n", nextId);
    printf("Name: %s\n", passengers[total].name);
    printf("Train: %s\n", trains[t - 1].name);
    printf("Route: %s\n", trains[t - 1].route);
    printf("Seat: %d\n", s);
    printf("Fare: Rs.%d\n", trains[t - 1].fare);

    total++;
    nextId++;
}


void showPassengers() {
    int i;

    if (total == 0) {
        printf("No passengers booked yet.\n");
        return;
    }

    printf("\n-- PASSENGER INFORMATION --\n");

    for (i = 0; i < total; i++) {
        printf("\nTicket ID: %d\n", passengers[i].id);
        printf("Name: %s\n", passengers[i].name);
        printf("Age: %d\n", passengers[i].age);
        printf("Gender: %c\n", passengers[i].gender);
        printf("Train: %s\n",
               trains[passengers[i].train - 1].name);
        printf("Seat: %d\n", passengers[i].seat);
    }

    printf("\nTotal bookings: %d\n", total);
}


void cancelTicket() {
    int id, i, pos = -1;

    printf("Enter ticket ID to cancel: ");
    scanf("%d", &id);

    for (i = 0; i < total; i++) {
        if (passengers[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Ticket not found!\n");
        return;
    }

    seats[passengers[pos].train - 1]
         [passengers[pos].seat - 1] = 0;

    for (i = pos; i < total - 1; i++) {
        passengers[i] = passengers[i + 1];
    }

    total--;

    printf("Ticket %d cancelled successfully!\n", id);
}


int main() {
    int choice;

    do {
        printf(" RAILWAY RESERVATION SYSTEM\n");
        printf("1. Book Ticket\n");
        printf("2. Check Seat Availability\n");
        printf("3. Passenger Information\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                checkSeats();
                break;
            case 3:
                showPassengers();
                break;
            case 4:
                cancelTicket();
                break;
            case 5:
                printf("Thank you for using our system!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}