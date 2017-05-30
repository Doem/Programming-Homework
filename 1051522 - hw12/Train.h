#ifndef TRAIN_H
#define TRAIN_H

#include <string>
using std::string;

class Train {
	public:
	string getTrainNumber();
	void setTrainNumber(string _trainNumber);

	string getDepartureTimes(int _station);
	void setDepartureTimes(int _station, string _departureTimes);

	private:
	char trainNumber[8];		// used to identify a train  車次號碼
	char departureTimes[13][8]; // the departure time of a train for each station  火車在各站的離站時間
	// departureTimes[0] is not used   departureTimes[0]未使用
};

string Train::getTrainNumber() {
	return trainNumber;
}

void Train::setTrainNumber(string _trainNumber) {
	strcpy_s(trainNumber, _trainNumber.c_str());
}

string Train::getDepartureTimes(int _station) {
	return departureTimes[_station];
}

void Train::setDepartureTimes(int _station, string _departureTimes) {
	strcpy_s(departureTimes[_station], _departureTimes.c_str());
}
#endif