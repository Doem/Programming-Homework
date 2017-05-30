#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "TimeTable.h"
#include "ReservationDataBase.h"
#include "ViewCancelReservation.h"
using namespace std;

void displayMainMenu();
int inputAnInteger(int begin, int end);

int main() {
	bool userExited = false;

	TimeTable timeTable;
	ReservationDataBase reservationDataBase;

	cout << "Taiwan High Speed Rail Booking System\n";

	while (!userExited) {
		displayMainMenu();
		int choice = inputAnInteger(1, 3);
		
		if (choice == 1)
			reservationDataBase.makeReservation();
		else if (choice == 2) {
			ViewCancelReservation viewCancelReservation(reservationDataBase.getReservationDataBase());

			viewCancelReservation.execute();
		}
		else if (choice == 3)
			userExited = true;
	}

	return 0;
}

void displayMainMenu() {
	cout << "\nEnter Your Choice\n"
		<< "1. Booking\n"
		<< "2. Booking History\n"
		<< "3. End Program\n"
		<< "? ";
}

int inputAnInteger(int begin, int end) {
	while (1) {
		int number;
		string input;
		stringstream ss;

		getline(cin, input);
		ss << input; ss >> number;
		if (number >= begin && number <= end)
			return number;
		else
			cout << "\nOut of range! Please try again: ";
	}
}