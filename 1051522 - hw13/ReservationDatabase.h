// ReservationDatabase.h
// ReservationDatabase class definition. Represents the reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include "vector.h"
//#include <vector>
#include "Reservation.h" // Reservation class definition

class ReservationDatabase {
	public:
	ReservationDatabase(); // constructor loads train reservations from the file Reservation details.dat
	~ReservationDatabase(); // destructor stores train reservations into the file Reservation details.dat

	// returns an iterator which points to a Reservation object with specified idNumber and reservationNumber
	vector< Reservation >::iterator searchReservation(string idNumber, string reservationNumber);
	vector< Reservation >::iterator end(); // returns reservations.end()

	// calls it->displayReservationDetails()
	void displayReservation(vector< Reservation >::iterator it);

	// cancels the Reservation object pointed by it
	void cancelReservation(vector< Reservation >::iterator it);

	// calls reservations.push_back( reservation );
	void addReservation(Reservation reservation);

	// reduces adultTickets and concessionTickets in the Reservation object pointed by it
	void reduceSeats(vector< Reservation >::iterator it);
	private:
	vector< Reservation > reservations; // vector of the train reservations

	void loadReservations(); // loads train reservations from the file Reservation details.dat
	void storeReservations(); // stores train reservations into the file Reservation details.dat
}; // end class ReservationDatabase

#endif // RESERVATION_DATABASE_H