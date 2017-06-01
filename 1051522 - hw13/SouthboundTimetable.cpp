// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h" // SouthboundTimetable class definition

extern string departureTimes[37];

// SouthboundTimetable default constructor loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable() {
	loadSouthboundTimetable();
}

int SouthboundTimetable::getNumberOfTrains() {
	return southboundTimetable.size();
}

vector< Train >::iterator SouthboundTimetable::searchTrain(string trainNumber) {
	for (auto it = southboundTimetable.begin(); it != southboundTimetable.end(); ++it)
		if (it->getTrainNumber() == trainNumber)	return it;
	return southboundTimetable.end();
}

void SouthboundTimetable::displayComingTrains(int departureTime, int originStation, int destinationStation) {
	int index = 0;
	int hour = (departureTimes[departureTime][0] - '0') * 10 + departureTimes[departureTime][1] - '0';
	int minute = (departureTimes[departureTime][3] - '0') * 10 + departureTimes[departureTime][4] - '0';
	
	cout << "\nTrain No.  Departure  Arrival\n";
	for (auto &station : southboundTimetable) {
		if (index >= 5)	break;
		if (station.getDepartureTimes(originStation) != "-" &&
			station.getDepartureTimes(destinationStation) != "-") {
			int _hour = (station.getDepartureTimes(originStation)[0] - '0') * 10 + station.getDepartureTimes(originStation)[1] - '0';
			int _minute = (station.getDepartureTimes(originStation)[3] - '0') * 10 + station.getDepartureTimes(originStation)[4] - '0';

			if (_hour >= hour && _minute >= minute) {
				++index;
				cout << right << setw(8) << station.getTrainNumber()
					<< setw(12) << station.getDepartureTimes(originStation)
					<< setw(9) << station.getDepartureTimes(destinationStation) << endl;
			}
		}
	}
}

void SouthboundTimetable::loadSouthboundTimetable() {
	fstream file("Southbound timetable.dat", ios::in | ios::binary);
	Train temp;

	if (!file) {
		cout << "\nCannot find the file \"Southbound timetable.dat\". Please try again!\n";
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(Train)))
		southboundTimetable.push_back(temp);
}