#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "MemberDatabase.h" // MemberDatabase class definition
class Transaction; // forward declaration of class Transaction

class Registration {
	public:
	Registration(MemberDatabase &); // constructor initializes data members
	void execute(); // start the Registration
	private:
	MemberInfo newMember; // a new member
	MemberDatabase &memberDatabase; // member information database
}; // end class Registration


Registration::Registration(MemberDatabase &_MemberDatabase) 
	:memberDatabase(_MemberDatabase) {
}

void Registration::execute() {
	string _accountNumber, _password, _IDNumber, _name;

	while (1) {
		cout << "\nInput your ID Number: ";
		getline(cin, _IDNumber);
		
		if (memberDatabase.duplicateID(_IDNumber)) {
			cout << "\nYou are already a member!\n";
			return;
		}

		cout << "\nInput your Name: ";
		getline(cin, _name);
		cout << "\nChoose an account number: ";
		break;
	}

	while (1) {
		getline(cin, _accountNumber);
		
		if (memberDatabase.duplicateAccount(_accountNumber)) {
			cout << "\nAccount number \"" << _accountNumber << "\" has been used.Please choose another one : ";
			continue;
		}

		cout << "\nChoose a password: ";
		getline(cin, _password);
		cout << "\nRegistration Completed!\n";
		break;
	}

	newMember.setAccountNumber(_accountNumber);
	newMember.setPassword(_password);
	newMember.setIDNumber(_IDNumber);
	newMember.setName(_name);
	memberDatabase.pushBack(newMember);
}
#endif