// MakingReservation.h
// MakingReservation class definition. Represents a making reservation.
#ifndef MAKING_RESERVATION_H
#define MAKING_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "SouthboundTimetable.h" // SouthboundTimetable class definition
#include "NorthboundTimetable.h" // SouthboundTimetable class definition

class MakingReservation {
	public:
	MakingReservation(ReservationDatabase &theReservationDatabase,
					  SouthboundTimetable &theSouthboundTimetable,
					  NorthboundTimetable &theNorthboundTimetable);
	void execute(); // perform making reservation
	private:
	Reservation reservation;
	ReservationDatabase &reservationDatabase; // reference to the reservation database
	SouthboundTimetable &southboundTimetable; // reference to the southbound timetable
	NorthboundTimetable &northboundTimetable; // reference to the northbound timetable

	void inputReservationDetails(int &departureTime); // inputs originStation, destinationStation, carClass,
	// date, departureTime, adultTickets and concessionTickets
	void chooseTrain(int departureTime); // displays timetables for 5 coming trains, then let user choose a train
	void inputContactPersonInfo(); // inputs idNumber and phone, and randomly generate reservationNumber
}; // end class MakingReservation

#endif // MAKING_RESERVATION_H