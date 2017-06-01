#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

// ReservationHistory default constructor
ReservationHistory::ReservationHistory(ReservationDatabase &theReservationDatabase,
									   SouthboundTimetable &theSouthboundTimetable,
									   NorthboundTimetable &theNorthboundTimetable)
									   : reservationDatabase(theReservationDatabase),
									   southboundTimetable(theSouthboundTimetable),
									   northboundTimetable(theNorthboundTimetable) {
} // end ReservationHistory default constructor

void ReservationHistory::execute() {
	int choice;

	cout << "\nEnter ID Number: ";
	cin >> idNumber;
	
	cout << "\nEnter Reservation Number: ";
	cin >> reservationNumber;

	auto it = reservationDatabase.searchReservation(idNumber, reservationNumber);
	if (it == reservationDatabase.end()) {
		cout << "\nReservation record not found!\n";
		return;
	}

	reservationDatabase.displayReservation(it);

	while ((choice = enterChoice()) != 3) {
		switch (choice) {
			case 1:
				reservationDatabase.cancelReservation(it);
				break;
			case 2:
				reservationDatabase.reduceSeats(it);
				break;
			default:
				cerr << "Incorrect Choice" << endl;
				break;
		}
	}
}

int ReservationHistory::enterChoice() {
	cout << "\nEnter Your Choice\n"
		<< "1. Cancellation\n"
		<< "2. Reduce\n"
		<< "3. Back to Main Menu\n? ";

	int menuChoice;
	cin >> menuChoice;
	return menuChoice;
}