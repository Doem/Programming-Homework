#ifndef NORTHBOUNDTIMETABLE_H
#define NORTHBOUNDTIMETABLE_H

#include "Train.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class TimeTable {
	public:
	TimeTable();

	protected:
	vector<Train> Northbound;
	vector<Train> Southbound;

	void loadTimeTable();
};

TimeTable::TimeTable() {
	loadTimeTable();
}

void TimeTable::loadTimeTable() {
	fstream file1("Northbound timetable.dat", ios::in | ios::binary);
	fstream file2("Southbound timetable.dat", ios::in | ios::binary);
	Train temp;

	if (!file1) {
		cout << "\nCannot find the file \"Northbound timetable.dat\". Please try again!" << endl;
		return;
	}
	else if (!file2) {
		cout << "\nCannot find the file \"Southbound timetable.dat\". Please try again!" << endl;
		return;
	}

	while (file1.read(reinterpret_cast<char*>(&temp), sizeof(Train)))
		Northbound.push_back(temp);
	while (file2.read(reinterpret_cast<char*>(&temp), sizeof(Train)))
		Southbound.push_back(temp);
}
#endif