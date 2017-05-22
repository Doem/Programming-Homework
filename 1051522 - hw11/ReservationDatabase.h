#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

//#include <vector>
#include "Vector.h"
#include "Reservation.h" // Reservation class definition

class ReservationDatabase {
	public:
	ReservationDatabase(); // constructor
	~ReservationDatabase(); // destructor

	bool empty(); // returns true if the ReservationDatabase is empty

	// returns true if the ReservationDatabase has no reservations with specified accountNumber
	bool exist(string accountNumber);

	// display all reservation informations for members with specified accountNumber
	void displayReservationInfo(string accountNumber);

	// cancels the n-th Reservation object containing specified accountNumber
	void cancelReservation(string accountNumber, int n);

	void pushBack(Reservation newReservation); // add an element at the end of reservations

	private:
	vector< Reservation > reservations; // Vector of the Party World's reservations

	void loadFromReservationFile(); // loads reservations from the file ReservationInfo.dat
	void saveToReservationFile(); // stores reservations into the file ReservationInfo.dat
}; // end class ReservationDatabase

ReservationDatabase::ReservationDatabase()
	:reservations(1) {
	loadFromReservationFile();
}

ReservationDatabase::~ReservationDatabase() {
	saveToReservationFile();
}

bool ReservationDatabase::empty() {
	return (reservations.size() == 0);
}

bool ReservationDatabase::exist(string accountNumber) {
	for (auto &reservation : reservations)
		if (reservation.getAccountNumber() == accountNumber)	return false;
	return true;
}

void ReservationDatabase::displayReservationInfo(string accountNumber) {
	int index = 0;
	for (auto &reservation : reservations) {
		if (reservation.getAccountNumber() == accountNumber) {
			cout << ++index << ".";
			reservation.displayReservationInfo();
		}
	}
}

void ReservationDatabase::cancelReservation(string accountNumber, int n) {
	int index = 0;
	for (auto it = reservations.begin(); it != reservations.end(); ++it) {
		if (it->getAccountNumber() == accountNumber)	++index;
		if (index == n) {
			cout << "\nReservation Cancelled!\n";
			reservations.erase(it);
			break;
		}
	}

	if (n > index)
		cout << "\nInvalid index\n";
}

void ReservationDatabase::pushBack(Reservation newReservation) {
	reservations.push_back(newReservation);
}

void ReservationDatabase::loadFromReservationFile() {
	fstream file("ReservationInfo.dat", ios::in | ios::binary);
	Reservation temp;

	if (!file) {
		fstream file("ReservationInfo.dat", ios::out);
		cout << "\nCannot open ReservationInfo.dat. Please try again!\n";
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(Reservation)))
		reservations.push_back(temp);
}

void ReservationDatabase::saveToReservationFile() {
	fstream file("ReservationInfo.dat", ios::out | ios::binary);

	for (auto &reservation : reservations)
		file.write(reinterpret_cast<char*>(&reservation), sizeof(Reservation));
}
#endif