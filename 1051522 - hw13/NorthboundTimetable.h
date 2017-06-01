// NorthboundTimetable.h
// NorthboundTimetable class definition. Represents the northbound timetable.
#ifndef NORTHBOUND_TIMETABLE_H
#define NORTHBOUND_TIMETABLE_H

#include "vector.h" // class uses vector to store NorthboundTimetable objects
//#include <vector>
#include "Train.h" // Train class definition

class NorthboundTimetable {
	public:
	NorthboundTimetable(); // call loadNorthboundTimetable()
	int getNumberOfTrains(); // returns the total number of northbound trains

	// returns an iterator which points to the northbound train with the specified trainNumber
	vector< Train >::iterator searchTrain(string trainNumber);

	// display timetables for 5 coming northbound trains with
	// the departure time for the origin station >= departureTimes[ departureTime ],
	// the departure time for the origin station != "-", and
	// the departure time for the destination station != "-"
	void displayComingTrains(int departureTime, int originStation, int destinationStation);
	private:
	vector< Train > northboundTimetable; // the northbound timetable

	// loads the northbound timetable from the file "Northbound timetable.dat"
	void loadNorthboundTimetable();
}; // end class NorthboundTimetable

#endif // NORTHBOUND_TIMETABLE_H