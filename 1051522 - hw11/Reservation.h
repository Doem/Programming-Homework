// Reservation.h
// Reservation class definition. Represents a reservation.
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using std::string;

class Reservation {
	public:
	Reservation(string theAccountNumber = "", string theBranch = "", string theDate = "",
				string theHour = "", string theRoomType = "", int theCustomerNumber = 0) {};
	void setAccountNumber(string theAccountNumber);
	void setBranch(string theBranch);
	void setDate(string theDate);
	void setHour(string theHour);
	void setRoomType(string theRoomType);
	void setCustomerNumber(int theCustomerNumber);
	string getAccountNumber();
	string getBranch();
	string getDate();
	string getHour();
	string getRoomType();
	int getCustomerNumber();

	// displays accountNumber, branch, date, hour, roomType, customerNumber
	void displayReservationInfo();
	private:
	char accountNumber[24]; // 帳號
	char branch[24];        // 分店
	char date[12];          // 預約日期
	char hour[4];           // 預約小時
	char roomType[16];       // 包廂類型
	int customerNumber;     // 消費人數
};


void Reservation::setAccountNumber(string theAccountNumber) {
	strcpy_s(accountNumber, theAccountNumber.c_str());
}

void Reservation::setBranch(string theBranch) {
	strcpy_s(branch, theBranch.c_str());
}

void Reservation::setDate(string theDate) {
	strcpy_s(date, theDate.c_str());
}

void Reservation::setHour(string theHour) {
	strcpy_s(hour, theHour.c_str());
}

void Reservation::setRoomType(string theRoomType) {
	strcpy_s(roomType, theRoomType.c_str());
}

void Reservation::setCustomerNumber(int theCustomerNumber) {
	customerNumber = theCustomerNumber;
}

string Reservation::getAccountNumber() {
	return string(accountNumber);
}

string Reservation::getBranch() {
	return string(branch);
}

string Reservation::getDate() {
	return string(date);
}

string Reservation::getHour() {
	return string(hour);
}

string Reservation::getRoomType() {
	return string(roomType);
}

int Reservation::getCustomerNumber() {
	return customerNumber;
}

void Reservation::displayReservationInfo() {
	cout << right << setw(15) << accountNumber
		<< setw(26) << branch
		<< setw(14) << date
		<< setw(8) << hour
		<< setw(13) << roomType
		<< setw(19) << customerNumber << endl;
}
#endif