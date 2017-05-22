// MakeReservation.h
// MakeReservation class definition.
#ifndef MAKE_RESERVATION_H
#define MAKE_RESERVATION_H

#include "Transaction.h" // Transaction class definition
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include <sstream>
using std::stringstream;

struct Date {
	int year;
	int month;
	int day;
	int hour;
};

class MakeReservation : public Transaction {
	public:
	MakeReservation(string, ReservationDatabase &); // constructor
	virtual void execute(); // perform the transaction
	private:
	Reservation newReservation; // a new reservation

	int inputAnInteger(int begin, int end); // input an integer in the range [ begin, end ]
}; // end class MakeReservation

MakeReservation::MakeReservation(string _accountNumber, ReservationDatabase &_ReservationDatabase)
	:Transaction(_accountNumber, _ReservationDatabase) {
}

void MakeReservation::execute() {
	char branches[16][25] = { "", "Taipei Dunhua South", "Taipei SOGO", "Taipei Songjiang", "Taipei Nanjing", "Taipei Linsen", "Taipei Zhonghua New", "Banqiao Guanqian", "Yonghe Lehua", "Taoyuan Zhonghua", "Zhongli Zhongyang", "Hsinchu Beida", "Taichung Ziyou", "Chiayi Ren'ai", "Tainan Ximen", "Kaohsiung Zhonghua New" };
	string temp;
	stringstream ss;

	newReservation.setAccountNumber(getAccountNumber());

	cout << endl;
	for (int i = 1; i <= 15; ++i)
		cout << right << setw(2) << i << ". " << branches[i] << endl;
	cout << "\nEnter your choice: ";
	newReservation.setBranch(string(branches[inputAnInteger(1, 15)]));

	cout << "\nEnter date (yyyy-mm-dd): ";
	getline(cin, temp);
	newReservation.setDate(temp);

	cout << "\nEnter hour (0бу23): ";
	ss << inputAnInteger(0, 23); ss >> temp;
	newReservation.setHour(temp);

	cout << "\nEnter the number of customers (1~30): ";
	newReservation.setCustomerNumber(inputAnInteger(1, 30));

	cout << "\n 1. Standard Room\n 2. Party Room\n\nEnter your choice: (1~2): ";
	switch (inputAnInteger(1, 2)) {
		case 1:
			newReservation.setRoomType(string("Standard"));
			break;
		case 2:
			newReservation.setRoomType(string("Party"));
			break;
	}
	cout << "\nReservation Completed!\n";
	getReservationDatabase().pushBack(newReservation);
}

int MakeReservation::inputAnInteger(int begin, int end) {
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
#endif // MAKE_RESERVATION_H