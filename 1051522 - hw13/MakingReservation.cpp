// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern string departureTimes[37];

// MakingReservation constructor
MakingReservation::MakingReservation(ReservationDatabase &theReservationDatabase,
									 SouthboundTimetable &theSouthboundTimetable,
									 NorthboundTimetable &theNorthboundTimetable)
									 : reservationDatabase(theReservationDatabase),
									 southboundTimetable(theSouthboundTimetable),
									 northboundTimetable(theNorthboundTimetable) {
} // end MakingReservation constructor

void MakingReservation::execute() {
	int departureTime;

	inputReservationDetails(departureTime);

	chooseTrain(departureTime); // displays timetables for 5 coming trains, then let user choose a train

	inputContactPersonInfo();

	reservation.displayReservationDetails();

	reservationDatabase.addReservation(reservation);

	cout << "\nReservation Completed!\n\n";
}

void MakingReservation::inputReservationDetails(int &departureTime) {
	char StationName[13][12] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli", "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };
	string str;
	int temp;

	cout << "\nOrigin Station\n";
	for (int i = 1; i <= 12; ++i)
		cout << i << ". " << StationName[i] << endl;
	cout << "? ";
	cin >> temp;
	reservation.setOriginStation(temp);

	cout << "\nDestination Station \n";
	for (int i = 1; i <= 12; ++i)
		cout << i << ". " << StationName[i] << endl;
	cout << "? ";
	cin >> temp;
	reservation.setDestinationStation(temp);

	cout << "\nCar Class\n1. Standard Car\n2. Business Car\n? ";
	cin >> temp;
	reservation.setCarClass(temp);

	cout << "\nDeparture Date: ";
	cin >> str;
	reservation.setDate(str);

	for (int i = 1; i < 37; ++i)
		cout << i << ". " << departureTimes[i] << endl;
	cout << "\nEnter Departure Time Code: ";
	cin >> departureTime;

	cout << "\nHow many adult tickets? ";
	cin >> temp;
	reservation.setAdultTickets(temp);

	cout << "\nHow many concession tickets? ";
	cin >> temp;
	reservation.setConcessionTickets(temp);
}

void MakingReservation::chooseTrain(int departureTime) {
	string temp;

	if (reservation.getOriginStation() < reservation.getDestinationStation())
		southboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
	else if (reservation.getOriginStation() > reservation.getDestinationStation())
		northboundTimetable.displayComingTrains(departureTime, 13 - reservation.getOriginStation(), 13 - reservation.getDestinationStation());

	cout << "\nEnter Train Number: ";
	cin >> temp;
	reservation.setTrainNumber(temp);
}

void MakingReservation::inputContactPersonInfo() {
	string str;

	cout << "\nEnter Contact Person Information\n";

	cout << "\nID Number: ";
	cin >> str;
	reservation.setIdNumber(str);

	cout << "\nPhone: ";
	cin >> str;
	reservation.setPhone(str);

	reservation.setReservationNumber(str);
	cout << "\nReservation Number: " << reservation.getReservationNumber() << endl;
}