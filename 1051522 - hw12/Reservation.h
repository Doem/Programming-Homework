#ifndef RESERVATION_H
#define RESERVATION_H

#include <time.h>
#include <string>
#include <stdlib.h>
using namespace std;

class Reservation {
	public:
	Reservation();
	string getReservationNumber();
	void setReservationNumber();

	string getTrainNumber();
	void setTrainNumber(string _trainNumber);

	string getIdNumber();
	void setIdNumber(string _idNumber);
	
	string getPhone();
	void setPhone(string _phone);

	string getDate();
	void setDate(string _date);

	int getOriginStation();
	void setOriginStation(int _originStation);

	int getDestinationStation();
	void setDestinationStation(int _destinationStation);

	int getCarClass();
	void setCarClass(int _carClass);

	int getAdultTickets();
	void setAdultTickets(int _adultTickets);

	int getConcessionTickets();
	void setConcessionTickets(int _concessionTickets);

	private:
	char reservationNumber[12]; // used to identify a reservation  �q��N��
	char trainNumber[8];		// used to identify a train  �������X
	char idNumber[12];			// the id number of the contact person  �����H�������Ҧr��
	char phone[12];				// the (local or mobile) phone number of the contact person  �����H���p���q��
	char date[12];				// outbound date  �f�����
	int originStation;			// the origin station code  �_�{���N�X
	int destinationStation;		// the destination station code  ��F���N�X
	int carClass;				// the car class code; 1:standard car, 2:business car  ���[����; 1:�зǨ��[, 2:�ӰȨ��[
	int adultTickets;			// the number of adult tickets  �����i��
	int concessionTickets;		// the number of concession tickets  �u�ݲ��i��
};

Reservation::Reservation() {
	
}

string Reservation::getReservationNumber() {
	return reservationNumber;
}

void Reservation::setReservationNumber() {
	srand(time(NULL));
	for (int i = 0; i < 8; ++i)
		reservationNumber[i] = rand() % 10 + '0';
	reservationNumber[8] = '\0';
}

string Reservation::getTrainNumber() {
	return trainNumber;
}

void Reservation::setTrainNumber(string _trainNumber) {
	strcpy_s(trainNumber, _trainNumber.c_str());
}

string Reservation::getIdNumber() {
	return idNumber;
}

void Reservation::setIdNumber(string _idNumber) {
	strcpy_s(idNumber, _idNumber.c_str());
}

string Reservation::getPhone() {
	return phone;
}

void Reservation::setPhone(string _phone) {
	strcpy_s(phone, _phone.c_str());
}

string Reservation::getDate() {
	return date;
}

void Reservation::setDate(string _date) {
	strcpy_s(date, _date.c_str());
}

int Reservation::getOriginStation() {
	return originStation;
}

void Reservation::setOriginStation(int _originStation) {
	originStation = _originStation;
}

int Reservation::getDestinationStation() {
	return destinationStation;
}

void Reservation::setDestinationStation(int _destinationStation) {
	destinationStation = _destinationStation;
}

int Reservation::getCarClass() {
	return carClass;
}

void Reservation::setCarClass(int _carClass) {
	carClass = _carClass;
}

int Reservation::getAdultTickets() {
	return adultTickets;
}

void Reservation::setAdultTickets(int _adultTickets) {
	adultTickets = _adultTickets;
}

int Reservation::getConcessionTickets() {
	return concessionTickets;
}

void Reservation::setConcessionTickets(int _concessionTickets) {
	concessionTickets = _concessionTickets;
}

#endif