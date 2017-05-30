#ifndef VIEWCANCELRESERVATION_H
#define VIEWCANCELRESERVATION_H

#include "TimeTable.h"
#include "Reservation.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;


class ViewCancelReservation:public TimeTable {
	public:
	ViewCancelReservation(vector<Reservation>&);

	void execute();
	void displayMainMenu();
	private:
	int index;
	vector<Reservation> &reservationDataBase;

	void showReservation(int index);
	int inputAnInteger(int begin, int end);
};

ViewCancelReservation::ViewCancelReservation(vector<Reservation> &_reservationDataBase) 
	:reservationDataBase(_reservationDataBase) , index(-1){
}

void ViewCancelReservation::execute() {
	string IDNumber, ReservationNumber;

	cout << "\nEnter ID Number: ";
	cin >> IDNumber;
	
	cout << "\nEnter Reservation Number: ";
	cin >> ReservationNumber;
	cin.ignore();
	for (int i = 0; i < reservationDataBase.size(); ++i) {
		if (reservationDataBase[i].getIdNumber() == IDNumber && reservationDataBase[i].getReservationNumber() == ReservationNumber) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "\nReservation record not found!\n";
		return;
	}

	showReservation(index);
	

	while (1) {
		displayMainMenu();
		int choice = inputAnInteger(1, 3);
		int temp1, temp2;

		if (choice == 1) {
			if (index != -1) {
				auto it = reservationDataBase.begin();
				for (int i = 0; i < index; ++i, ++it);
				reservationDataBase.erase(it);
				cout << "\nReservation Cancelled!\n";
				index = -1;
			}
			else
				cout << "\nReservation Cancelled!\n";
		}
		else if (choice == 2) {
			if (index != -1) {
				cout << "\nHow many adult tickets to cancel¡H ";
				cin >> temp1;
				cout << "How many concession tickets to cancel¡H ";
				cin >> temp2;
				cin.ignore();

				reservationDataBase[index].setAdultTickets(reservationDataBase[index].getAdultTickets() - temp1);
				reservationDataBase[index].setConcessionTickets(reservationDataBase[index].getConcessionTickets() - temp2);

				if (reservationDataBase[index].getAdultTickets() == 0 && reservationDataBase[index].getConcessionTickets() == 0) {
					auto it = reservationDataBase.begin();
					for (int i = 0; i < index; ++i, ++it);
					reservationDataBase.erase(it);
					cout << "\nReservation Cancelled!\n";
					index = -1;
				}
				else
					showReservation(index);
				cout << "\nYou have successfully reduced the number of tickets!\n";
			}
			else
				cout << "\nReservation Cancelled!\n";
		}
		else if (choice == 3)
			return;
	}
}

void ViewCancelReservation::displayMainMenu() {
	cout << "\nEnter Your Choice\n"
		<< "1. Cancellation\n"
		<< "2. Reduce\n"
		<< "3. Back to Main Menu\n"
		<< "? ";
}

void ViewCancelReservation::showReservation(int index) {
	char carTypes[3][10] = { "", "Standard", "Business" };
	cout << "\nTrain No.    From        To        Date  Departure  Arrival   Adult  Concession  Fare     Class\n";
	cout << right << setw(8) << reservationDataBase[index].getTrainNumber()
		<< setw(9) << StationName[reservationDataBase[index].getOriginStation()]
		<< setw(10) << StationName[reservationDataBase[index].getDestinationStation()]
		<< setw(12) << reservationDataBase[index].getDate();
	
	if (reservationDataBase[index].getOriginStation() < reservationDataBase[index].getDestinationStation()) {
		for (int i = 0; i < Southbound.size(); ++i) {
			if (Southbound[i].getTrainNumber() == reservationDataBase[index].getTrainNumber())
				cout << right << setw(11) << Southbound[i].getDepartureTimes(reservationDataBase[index].getOriginStation())
				<< setw(9) << Southbound[i].getDepartureTimes(reservationDataBase[index].getDestinationStation());
		}
	}
	else if (reservationDataBase[index].getOriginStation() > reservationDataBase[index].getDestinationStation()) {
		for (int i = 0; i < Northbound.size(); ++i) {
			if (Northbound[i].getTrainNumber() == reservationDataBase[index].getTrainNumber())
				cout << right << setw(11) << Northbound[i].getDepartureTimes(reservationDataBase[index].getOriginStation())
				<< setw(9) << Northbound[i].getDepartureTimes(reservationDataBase[index].getDestinationStation());
		}
	}
	
	cout << right << setw(6) << adultTicketPrice[reservationDataBase[index].getDestinationStation()][reservationDataBase[index].getOriginStation()] << "*" << reservationDataBase[index].getAdultTickets()
		<< setw(10) << concessionTicketPrice[reservationDataBase[index].getDestinationStation()][reservationDataBase[index].getOriginStation()] << "*" << reservationDataBase[index].getConcessionTickets()
		<< setw(6) << adultTicketPrice[reservationDataBase[index].getDestinationStation()][reservationDataBase[index].getOriginStation()] * reservationDataBase[index].getAdultTickets() + concessionTicketPrice[reservationDataBase[index].getDestinationStation()][reservationDataBase[index].getOriginStation()] * reservationDataBase[index].getConcessionTickets()
		<< setw(10) << carTypes[reservationDataBase[index].getCarClass()] << endl;
}

int ViewCancelReservation::inputAnInteger(int begin, int end) {
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
#endif