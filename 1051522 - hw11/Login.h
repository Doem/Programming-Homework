#ifndef LOGIN_H
#define LOGIN_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "MemberDatabase.h" // MemberDatabase class definition

#include "MakeReservation.h"
#include "ViewCancelReservation.h"
#include <sstream>
using std::stringstream;

class Transaction; // forward declaration of class Transaction

class Login {
	public:
	Login(MemberDatabase &, ReservationDatabase &); // constructor initializes data members
	void execute(); // start the Login
	private:
	bool userAuthenticated; // whether user is authenticated
	string currentAccountNumber; // current user's account number
	MemberDatabase &memberDatabase; // member information database
	ReservationDatabase &reservationDatabase; // reservation information database

	void authenticateUser(); // attempts to authenticate user
	void performTransactions(); // performs transactions
	void displaySubMenu() const; // displays sub menu

	int inputAnInteger(int begin, int end); // input an integer in the range [ begin, end ]
}; // end class Login


Login::Login(MemberDatabase &_MemberDatabase, ReservationDatabase &_ReservationDatabase)
	:userAuthenticated(false),
	currentAccountNumber(""),
	memberDatabase(_MemberDatabase),
	reservationDatabase(_ReservationDatabase) {
}

void Login::execute() {

	while (!userAuthenticated) {
		cout << "\nPlease enter your account number: ";
		getline(cin, currentAccountNumber);
		cout << "\nEnter your password: ";
		authenticateUser();
	}
	performTransactions();
	userAuthenticated = false;
}

void Login::authenticateUser() {
	string _password;

	getline(cin, _password);
	if (memberDatabase.authenticateUser(currentAccountNumber, _password))
		userAuthenticated = true;
	else
		cout << "\nInvalid account number or password. Please try again.\n";
}

void Login::performTransactions() {
	while (1) {
		displaySubMenu();
		int choice = inputAnInteger(1, 3);
		Transaction *transaction;

		if (choice == 1) {
			transaction = new MakeReservation(currentAccountNumber, reservationDatabase);
			transaction->execute();
			//delete transaction;
		}
		else if (choice == 2) {
			transaction = new ViewCancelReservation(currentAccountNumber, reservationDatabase);
			transaction->execute();
			//delete transaction;
		}
		else
			break;
	}
}

void Login::displaySubMenu() const {
	cout << "\n1 - Make Reservation\n";
	cout << "2 - Reservation Enquiry / Canceling\n";
	cout << "3 - End\n";
	cout << "\nEnter your choice : (1~3) : ";
}

int Login::inputAnInteger(int begin, int end) {
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
#endif