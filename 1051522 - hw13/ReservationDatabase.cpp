// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase() {
	loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase() {
	storeReservations();
}

vector< Reservation >::iterator ReservationDatabase::searchReservation(string idNumber, string reservationNumber) {
	for (auto it = reservations.begin(); it != reservations.end(); ++it) 
		if (it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber)	return it;
	return reservations.end();
}

vector< Reservation >::iterator ReservationDatabase::end() {
	return reservations.end();
}

void ReservationDatabase::displayReservation(vector< Reservation >::iterator it) {
	it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation(vector< Reservation >::iterator it) {
	swap(it, reservations.end());
	reservations.pop_back();
	cout << "\nReservation Cancelled!\n";
}

void ReservationDatabase::addReservation(Reservation reservation) {
	reservations.push_back(reservation);
}

void ReservationDatabase::reduceSeats(vector< Reservation >::iterator it) {
	int temp;

	cout << "\nHow many adult tickets to cancel¡H";
	cin >> temp;
	it->setAdultTickets(it->getAdultTickets() - temp);

	cout << "How many concession tickets to cancel¡H";
	cin >> temp;
	it->setConcessionTickets(it->getConcessionTickets() - temp);

	if (it->getAdultTickets() == 0 && it->getConcessionTickets() == 0)
		cancelReservation(it);
	else {
		displayReservation(it);
		cout << "\nYou have successfully reduced the number of tickets!\n";
	}

}

void ReservationDatabase::loadReservations() {
	fstream file("Reservation details.dat", ios::in | ios::binary);
	Reservation temp;

	if (!file) {
		cout << "\nCannot find the file \"Reservation details.dat\". Please try again!\n";
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(Reservation)))
		reservations.push_back(temp);
}

void ReservationDatabase::storeReservations() {
	fstream file("Reservation details.dat", ios::out);

	for (auto &reservation : reservations)
		file.write(reinterpret_cast<char*>(&reservation), sizeof(Reservation));
}