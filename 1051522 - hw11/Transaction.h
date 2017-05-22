// Transaction.h
// Transaction abstract base class definition.
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iomanip>
#include <iostream>
using namespace::std;

class ReservationDatabase; // forward declaration of class ReservationDatabase

class Transaction {
	public:
	// constructor initializes common features of all Transactions
	Transaction(string, ReservationDatabase &);

	virtual ~Transaction() {} // virtual destructor with empty body

	string getAccountNumber() const; // return account number
	ReservationDatabase &getReservationDatabase() const; // return reference to database

	// pure virtual function to perform the transaction
	virtual void execute() = 0; // overridden in derived classes
	private:
	string accountNumber; // indicates account involved
	ReservationDatabase &reservationDatabase; // reference to the reservationDatabase
}; // end class Transaction

Transaction::Transaction(string _accountNumber, ReservationDatabase &_ReservationDatabase)
	:accountNumber(_accountNumber),
	reservationDatabase(_ReservationDatabase) {
}

string Transaction::getAccountNumber() const {
	return accountNumber;
}

ReservationDatabase &Transaction::getReservationDatabase() const {
	return reservationDatabase;
}
#endif // TRANSACTION_H