// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h" // NorthboundTimetable class definition

extern string departureTimes[37];

// NorthboundTimetable default constructor loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable() {
	loadNorthboundTimetable();
}

int NorthboundTimetable::getNumberOfTrains() {
	return northboundTimetable.size();
}

vector< Train >::iterator NorthboundTimetable::searchTrain(string trainNumber) {
	for (auto it = northboundTimetable.begin(); it != northboundTimetable.end(); ++it)
		if (it->getTrainNumber() == trainNumber)	return it;
	return northboundTimetable.end();
}

void NorthboundTimetable::displayComingTrains(int departureTime, int originStation, int destinationStation) {
	int index = 0;
	int hour = (departureTimes[departureTime][0] - '0') * 10 + departureTimes[departureTime][1] - '0';
	int minute = (departureTimes[departureTime][3] - '0') * 10 + departureTimes[departureTime][4] - '0';

	cout << "\nTrain No.  Departure  Arrival\n";
	for (auto &station : northboundTimetable) {
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

void NorthboundTimetable::loadNorthboundTimetable() {
	fstream file("Northbound timetable.dat", ios::in | ios::binary);
	Train temp;

	if (!file) {
		cout << "\nCannot find the file \"Northbound timetable.dat\". Please try again!\n";
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(Train)))
		northboundTimetable.push_back(temp);
}