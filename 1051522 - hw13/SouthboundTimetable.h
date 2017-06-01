// SouthboundTimetable.h
// SouthboundTimetable class definition. Represents the southbound timetable.
#ifndef SOUTHBOUND_TIMETABLE_H
#define SOUTHBOUND_TIMETABLE_H

#include "vector.h" // class uses vector to store SouthboundTimetable objects
//#include <vector>
#include "Train.h" // Train class definition

class SouthboundTimetable {
	public:
	SouthboundTimetable(); // call loadSouthboundTimetable()
	int getNumberOfTrains(); // returns the total number of southbound trains

	// returns an iterator which points to the southbound train with the specified trainNumber
	vector< Train >::iterator searchTrain(string trainNumber);

	// display timetables for 5 coming southbound trains with
	// the departure time for the origin station >= departureTimes[ departureTime ],
	// the departure time for the origin station != "-", and
	// the departure time for the destination station != "-"
	void displayComingTrains(int departureTime, int originStation, int destinationStation);
	private:
	vector< Train > southboundTimetable; // the southbound timetable

	// loads the southbound timetable from the file "Southbound timetable.dat"
	void loadSouthboundTimetable();
}; // end class SouthboundTimetable

#endif // SOUTHBOUND_TIMETABLE_H
