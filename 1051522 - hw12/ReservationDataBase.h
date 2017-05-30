#ifndef RESERVATIONDATABASE_H
#define RESERVATIONDATABASE_H

#include "Reservation.h"
#include "TimeTable.h"

#include <map>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

int adultTicketPrice[13][13] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 400, 560, 735, 1060, 1205, 1325, 1500, 1830, 2000,
	0, 40, 0, 0, 350, 510, 680, 1000, 1140, 1280, 1455, 1780, 1950,
	0, 70, 40, 0, 320, 470, 640, 965, 1110, 1240, 1420, 1740, 1910,
	0, 200, 160, 130, 0, 320, 495, 805, 965, 1095, 1260, 1590, 1760,
	0, 330, 290, 260, 130, 0, 325, 655, 805, 925, 1110, 1430, 1600,
	0, 480, 430, 400, 280, 140, 0, 485, 630, 760, 925, 1260, 1430,
	0, 750, 700, 670, 540, 410, 270, 0, 320, 440, 615, 940, 1110,
	0, 870, 820, 790, 670, 540, 390, 130, 0, 295, 460, 800, 965,
	0, 970, 930, 900, 780, 640, 500, 230, 110, 0, 340, 660, 830,
	0, 1120, 1080, 1050, 920, 790, 640, 380, 250, 150, 0, 495, 655,
	0, 1390, 1350, 1320, 1190, 1060, 920, 650, 530, 420, 280, 0, 325,
	0, 1530, 1490, 1460, 1330, 1200, 1060, 790, 670, 560, 410, 140, 0 };

// top-right: ticket fares for business car, bottom-left: ticket fares for standard car
int concessionTicketPrice[13][13] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 250, 350, 460, 665, 755, 830, 940, 1145, 1250,
	0, 20, 0, 0, 220, 320, 425, 625, 715, 800, 910, 1115, 1220,
	0, 35, 20, 0, 200, 295, 400, 605, 695, 775, 890, 1090, 1195,
	0, 100, 80, 65, 0, 200, 310, 505, 605, 685, 790, 995, 1100,
	0, 165, 145, 130, 65, 0, 205, 410, 505, 580, 695, 895, 1000,
	0, 240, 215, 200, 140, 70, 0, 305, 395, 475, 580, 790, 895,
	0, 375, 350, 335, 270, 205, 135, 0, 200, 275, 385, 590, 695,
	0, 435, 410, 395, 335, 270, 195, 65, 0, 185, 290, 500, 605,
	0, 485, 465, 450, 390, 320, 250, 115, 55, 0, 215, 415, 520,
	0, 560, 540, 525, 460, 395, 320, 190, 125, 75, 0, 310, 410,
	0, 695, 675, 660, 595, 530, 460, 325, 265, 210, 140, 0, 205,
	0, 765, 745, 730, 665, 600, 530, 395, 335, 280, 205, 70, 0 };

char StationName[13][12] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli", "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

char departureTimes[37][8] = { "",
"06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
"10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
"14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
"18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
"22:00", "22:30", "23:00", "23:30" };

class ReservationDataBase :public TimeTable {
	public:
	ReservationDataBase();
	~ReservationDataBase();

	bool empty();
	void makeReservation();
	vector<Reservation> &getReservationDataBase() { return reservationDataBase; };

	private:
	vector<string> Days;
	Reservation newReservation;
	vector<Reservation> reservationDataBase;
	map<string, pair<string, string>> trainList;

	void getDay();
	void showReservation();
	void loadReservationInfo();
	void saveReservationInfo();
	void showTrainTable(int DepartureTimeCode);
	int inputAnInteger(int begin, int end);
};

ReservationDataBase::ReservationDataBase() {
	loadReservationInfo();
}

ReservationDataBase::~ReservationDataBase() {
	saveReservationInfo();
}

bool ReservationDataBase::empty() {
	return reservationDataBase.empty();
}


void ReservationDataBase::makeReservation() {
	int DepartureTimeCode, temp;
	string str;
	stringstream ss;

	cout << "\nOrigin Station\n";
	for (int i = 1; i <= 12; ++i)
		cout << i << ". " << StationName[i] << endl;
	cout << "? ";
	newReservation.setOriginStation(inputAnInteger(1, 12));

	cout << "\nDestination Station\n";
	for (int i = 1; i <= 12; ++i)
		cout << i << ". " << StationName[i] << endl;
	cout << "? ";
	newReservation.setDestinationStation(inputAnInteger(1, 12));

	cout << "\nCar Class\n";
	cout << "1. Standard Car\n2. Business Car\n? ";
	newReservation.setCarClass(inputAnInteger(1, 2));

	getDay();
	cout << "\nDeparture Date: \n";
	for (int i = 0; i < Days.size(); ++i)
		cout << i + 1 << ". " << Days[i] << endl;
	cout << "? ";
	newReservation.setDate(Days[inputAnInteger(1, 7) - 1]);

	cout << endl;
	for (int i = 1; i <= 34; ++i)
		cout << i << ". " << departureTimes[i] << endl;
	cout << "\nEnter Departure Time Code: ";
	cin >> DepartureTimeCode;

	cout << "\nHow many adult tickets? ";
	cin >> temp;
	newReservation.setAdultTickets(temp);

	cout << "\nHow many concession tickets? ";
	cin >> temp;
	newReservation.setConcessionTickets(temp);

	cout << "\nTrain No.  Departure  Arrival\n";
	showTrainTable(DepartureTimeCode);
	cout << "\nEnter Train Number: ";
	cin >> temp; ss << temp;
	newReservation.setTrainNumber(ss.str());

	cout << "\nEnter Contact Person Information\n";
	cout << "\nID Number: ";
	cin >> str;
	newReservation.setIdNumber(str);

	cout << "Phone: ";
	cin >> str;
	newReservation.setPhone(str);

	newReservation.setReservationNumber();
	cout << "\nReservation Number: " << newReservation.getReservationNumber() << endl;

	showReservation();
	cout << "\nReservation Completed!\n";
	reservationDataBase.push_back(newReservation);
	cin.ignore();
}

void ReservationDataBase::getDay() {
	time_t rawTime;
	tm *timeInfo;
	char buffer[80];

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	for (int i = 1; i <= 7; ++i) {
		strftime(buffer, 80, "%Y-%m-%d", timeInfo);
		Days.push_back(buffer);
		timeInfo->tm_mday += 1;
		mktime(timeInfo);
	}
}

void ReservationDataBase::showReservation() {
	char carTypes[3][10] = { "", "Standard", "Business" };
	int adultTicketMoney = adultTicketPrice[newReservation.getDestinationStation()][newReservation.getOriginStation()] * newReservation.getAdultTickets();
	int concessionTicketMoney = concessionTicketPrice[newReservation.getDestinationStation()][newReservation.getOriginStation()] * newReservation.getConcessionTickets();
	
	cout << "\nTrain No.    From        To        Date  Departure  Arrival   Adult  Concession  Fare     Class\n";
	cout << right << setw(8) << newReservation.getTrainNumber()
		<< setw(9) << StationName[newReservation.getOriginStation()]
		<< setw(10) << StationName[newReservation.getDestinationStation()]
		<< setw(12) << newReservation.getDate()
		<< setw(11) << trainList[newReservation.getTrainNumber()].first
		<< setw(9) << trainList[newReservation.getTrainNumber()].second
		<< setw(6) << adultTicketPrice[newReservation.getDestinationStation()][newReservation.getOriginStation()] << "*" << newReservation.getAdultTickets()
		<< setw(10) << concessionTicketPrice[newReservation.getDestinationStation()][newReservation.getOriginStation()] << "*" << newReservation.getConcessionTickets()
		<< setw(6) << adultTicketMoney + concessionTicketMoney
		<< setw(10) << carTypes[newReservation.getCarClass()] << endl;
}

void ReservationDataBase::showTrainTable(int DepartureTimeCode) {
	int index = 0;
	int hour = (departureTimes[DepartureTimeCode][0] - '0') * 10 + (departureTimes[DepartureTimeCode][1] - '0');
	int minute = (departureTimes[DepartureTimeCode][3] - '0') * 10 + (departureTimes[DepartureTimeCode][4] - '0');

	if (newReservation.getOriginStation() < newReservation.getDestinationStation()) {
		for (int i = 0; i < Southbound.size() && index < 5; ++i) {
			if (Southbound[i].getDepartureTimes(newReservation.getOriginStation()) == "-")	continue;
			int trainHour = (Southbound[i].getDepartureTimes(newReservation.getOriginStation())[0] - '0') * 10 + (Southbound[i].getDepartureTimes(newReservation.getOriginStation())[1] - '0');
			int trainMinute = (Southbound[i].getDepartureTimes(newReservation.getOriginStation())[3] - '0') * 10 + (Southbound[i].getDepartureTimes(newReservation.getOriginStation())[4] - '0');

			if ((trainHour > hour) || (trainHour == hour && trainMinute >= minute)) {
				trainList.insert(pair<string, pair<string, string>>(Southbound[i].getTrainNumber(), pair<string, string>(Southbound[i].getDepartureTimes(newReservation.getOriginStation()), Southbound[i].getDepartureTimes(newReservation.getDestinationStation()))));
				cout << right << setw(8) << Southbound[i].getTrainNumber()
					<< setw(12) << Southbound[i].getDepartureTimes(newReservation.getOriginStation())
					<< setw(9) << Southbound[i].getDepartureTimes(newReservation.getDestinationStation()) << endl;
				++index;
			}
		}
	}
	else if (newReservation.getOriginStation() > newReservation.getDestinationStation()) {
		for (int i = 0; i < Northbound.size() && index < 5; ++i) {
			if (Northbound[i].getDepartureTimes(newReservation.getOriginStation()) == "-")	continue;
			int trainHour = (Northbound[i].getDepartureTimes(newReservation.getOriginStation())[0] - '0') * 10 + (Northbound[i].getDepartureTimes(newReservation.getOriginStation())[1] - '0');
			int trainMinute = (Northbound[i].getDepartureTimes(newReservation.getOriginStation())[3] - '0') * 10 + (Northbound[i].getDepartureTimes(newReservation.getOriginStation())[4] - '0');

			if ((trainHour > hour) || (trainHour == hour && trainMinute >= minute)) {
				trainList.insert(pair<string, pair<string, string>>(Northbound[i].getTrainNumber(), pair<string, string>(Northbound[i].getDepartureTimes(newReservation.getOriginStation()), Northbound[i].getDepartureTimes(newReservation.getDestinationStation()))));
				cout << right << setw(8) << Northbound[i].getTrainNumber()
					<< setw(12) << Northbound[i].getDepartureTimes(newReservation.getOriginStation())
					<< setw(9) << Northbound[i].getDepartureTimes(newReservation.getDestinationStation()) << endl;
				++index;
			}
		}
	}
}

int ReservationDataBase::inputAnInteger(int begin, int end) {
	while (1) {
		int number;
		string input;
		stringstream ss;

		getline(cin, input);
		ss << input; ss >> number;
		if (number >= begin && number <= end)
			return number;
		else
			cout << "\nOut of range! Please try again: ";
	}
}

void ReservationDataBase::loadReservationInfo() {
	fstream file("Reservation details.dat", ios::in | ios::binary);
	Reservation temp;

	if (!file) {
		cout << "\nCannot find the file \"Reservation details.dat\". Please try again!" << endl;
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(Reservation)))
		reservationDataBase.push_back(temp);
}

void ReservationDataBase::saveReservationInfo() {
	fstream file("Reservation details.dat", ios::out);

	for (auto &reservation : reservationDataBase)
		file.write(reinterpret_cast<char*>(&reservation), sizeof(Reservation));
}
#endif