#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Person {
protected:
    string name, email, phone;
public:
    void setPerson(string n, string e, string p) {
        name = n; email = e; phone = p;
    }
    string getName() { return name; }
};

class Passenger : public Person {
    string flightNum, seatNum;
public:
    void setPassengerDetails(string n, string e, string p, string fNum, string sNum) {
        setPerson(n, e, p);
        flightNum = fNum; seatNum = sNum;
    }
    void displayPassenger() {
        cout << "Name: " << name << ", Email: " << email << ", Phone: " << phone
             << ", Flight: " << flightNum << ", Seat: " << seatNum << endl;
    }
    string getFlightNumber() { return flightNum; }
};

class Flight {
    string flightNum, origin, destination;
    int seatsAvailable;
    float fare;
public:
    void setFlight(string fn, string o, string d, int s, float f) {
        flightNum = fn; origin = o; destination = d;
        seatsAvailable = s; fare = f;
    }
    string getFlightNumber() { return flightNum; }
    int getSeatsAvailable() { return seatsAvailable; }
    float getFare() { return fare; }
    void bookSeat() { seatsAvailable--; }
    void cancelSeat() { seatsAvailable++; }
    void displayFlight() {
        cout << "Flight: " << flightNum << ", From: " << origin
             << ", To: " << destination << ", Seats: " << seatsAvailable
             << ", Fare: $" << fare << endl;
    }
};

class Payment {
    string method;
    float amount;
public:
    void setPayment(string m, float a) {
        method = m; amount = a;
    }
    void displayPayment() {
        cout << "Payment Method: " << method << ", Amount: $" << amount << endl;
    }
};

class Ticket {
    string ticketNum, flightNum, passengerName;
public:
    void setTicket(string tNum, string fNum, string pName) {
        ticketNum = tNum; flightNum = fNum; passengerName = pName;
    }
    void displayTicket() {
        cout << "Ticket: " << ticketNum << ", Flight: " << flightNum
             << ", Passenger: " << passengerName << endl;
    }
};

class Admin {
    string username, password;
public:
    void setAdmin(string u, string p) {
        username = u; password = p;
    }
    bool login(string u, string p) {
        return username == u && password == p;
    }
};

int main() {
    Flight flights[10];
    Passenger passengers[100];
    Payment payments[100];
    Ticket tickets[100];

    int flightCount = 0, passengerCount = 0, paymentCount = 0, ticketCount = 0;

    Admin admin;
    admin.setAdmin("admin", "password");

    flights[0].setFlight("AA101", "New York", "Los Angeles", 5, 250.0);
    flights[1].setFlight("AA102", "Los Angeles", "New York", 3, 230.0);
    flightCount = 2;

    int choice;
    do {
        cout << "\n===== Airline Reservation Menu =====\n";
        cout << "1. Admin Login\n2. Show Flights\n3. Book Flight\n4. Cancel Booking\n";
        cout << "5. Show Passengers\n6. Show Payments\n7. Show Tickets\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string username, password;
            cout << "Enter username: "; getline(cin, username);
            cout << "Enter password: "; getline(cin, password);
            if (admin.login(username, password))
                cout << "Admin login successful!\n";
            else
                cout << "Invalid username or password.\n";
        }

        else if (choice == 2) {
            for (int i = 0; i < flightCount; i++) {
                flights[i].displayFlight();
                cout << endl;
            }
        }

        else if (choice == 3) {
            string name, email, phone, flightNum;
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Email: "; getline(cin, email);
            cout << "Enter Phone: "; getline(cin, phone);
            cout << "Enter Flight Number: "; getline(cin, flightNum);

            bool found = false;
            for (int i = 0; i < flightCount; i++) {
                if (flights[i].getFlightNumber() == flightNum && flights[i].getSeatsAvailable() > 0) {
                    flights[i].bookSeat();
                    passengers[passengerCount].setPassengerDetails(name, email, phone, flightNum, "S1");
                    payments[paymentCount].setPayment("Credit Card", flights[i].getFare());
                    stringstream ss; ss << "T" << ticketCount + 1;
                    tickets[ticketCount].setTicket(ss.str(), flightNum, name);
                    passengerCount++;
                    paymentCount++;
                    ticketCount++;
                    cout << "Booking successful!\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Flight not found or no seats available.\n";
        }

        else if (choice == 4) {
            string cancelName;
            cout << "Enter passenger name to cancel: ";
            getline(cin, cancelName);
            bool cancelled = false;
            for (int i = 0; i < passengerCount; i++) {
                if (passengers[i].getName() == cancelName) {
                    string flightNum = passengers[i].getFlightNumber();
                    for (int j = i; j < passengerCount - 1; j++) {
                        passengers[j] = passengers[j + 1];
                        payments[j] = payments[j + 1];
                        tickets[j] = tickets[j + 1];
                    }
                    passengerCount--;
                    paymentCount--;
                    ticketCount--;
                    for (int k = 0; k < flightCount; k++) {
                        if (flights[k].getFlightNumber() == flightNum) {
                            flights[k].cancelSeat();
                            break;
                        }
                    }
                    cout << "Booking cancelled.\n";
                    cancelled = true;
                    break;
                }
            }
            if (!cancelled)
                cout << "Passenger not found.\n";
        }

        else if (choice == 5) {
            for (int i = 0; i < passengerCount; i++) {
                passengers[i].displayPassenger();
                cout << endl;
            }
        }

        else if (choice == 6) {
            for (int i = 0; i < paymentCount; i++) {
                payments[i].displayPayment();
                cout << endl;
            }
        }

        else if (choice == 7) {
            for (int i = 0; i < ticketCount; i++) {
                tickets[i].displayTicket();
                cout << endl;
            }
        }

    } while (choice != 0);

    return 0;
}
