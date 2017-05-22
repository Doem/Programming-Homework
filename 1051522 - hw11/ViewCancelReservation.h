// ViewCancelReservation.h
// ViewCancelReservation class definition. Represents a view cancel reservation.
#ifndef VIEW_CANCEL_RESERVATION_H
#define VIEW_CANCEL_RESERVATION_H

#include "Transaction.h" // Transaction class definition
#include "ReservationDatabase.h" // ReservationDatabase class definition

class ViewCancelReservation : public Transaction {
	public:
	ViewCancelReservation(string, ReservationDatabase &); // constructor
	virtual void execute(); // perform the transaction
}; // end class ViewCancelReservation

ViewCancelReservation::ViewCancelReservation(string _accountNumber, ReservationDatabase &_ReservationDatabase) 
	:Transaction(_accountNumber, _ReservationDatabase) {
}

void ViewCancelReservation::execute() {
	int number;
	string input;
	stringstream ss;

	if (getReservationDatabase().exist(getAccountNumber())) {
		cout << "\nNo reservation information!\n";
		return;
	}
	
	cout << "\n   Account Number                    Branch          Date    Hour    Room Type    No of Customers\n";
	getReservationDatabase().displayReservationInfo(getAccountNumber());
	
	cout << "\nChoose a reservation to cancel (0: keep all reservations): ";
	getline(cin, input);
	ss << input; ss >> number;

	if (number != 0)
		getReservationDatabase().cancelReservation(getAccountNumber(), number);
}
#endif // VIEW_CANCEL_RESERVATION_H