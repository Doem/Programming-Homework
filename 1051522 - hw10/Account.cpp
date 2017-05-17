#include "Account.h"
Account::Account() {
	fstream file("MemberInfo.dat", ios::in | ios::out | ios::binary);
	MemberInfo temp = { "", "", "", "" };

	if (!file) {
		fstream file1("MemberInfo.dat", ios::out | ios::binary);
		file.open("MemberInfo.dat", ios::in | ios::out | ios::binary);
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(MemberInfo)))
		member.push_back(temp);
	return;
}

string Account::getName(int index) {
	return string(member[index].name);
}

string Account::getIDNumber(int index) {
	return string(member[index].IDNumber);
}

string Account::getPassword(int index) {
	return string(member[index].password);
}

string Account::getAccountNumber(int index) {
	return string(member[index].accountNumber);
}

void Account::login() {
	string _accountNumber, _password;
	while (true) {
		cout << "\nPlease enter your account number: ";
		cin >> _accountNumber;
		cout << "\nEnter your password: ";
		cin >> _password;

		for (size_t i = 0; i < member.size(); ++i) {
			if (strcmp(member[i].accountNumber, _accountNumber.c_str()) == 0 &&
				strcmp(member[i].password, _password.c_str()) == 0) {
				setUser(member[i]);
				readReservationInfo(_accountNumber);
				cin.ignore();
				return;
			}
		}

		cout << "\nInvalid account number or password. Please try again.\n";
	}
}

void Account::registration() {
	MemberInfo newMember;
	string _accountNumber, _IDNumber, _password, _name;
	bool chk = true;
	
	cout << "\nInput your ID Number: ";
	getline(cin, _IDNumber);
	for (size_t i = 0; i < member.size(); ++i) {
		if (strcmp(member[i].IDNumber, _IDNumber.c_str()) == 0) {
			cout << "\nYou are already a member!\n";
			return;
		}
	}

	cout << "\nInput your Name: ";
	getline(cin, _name);
	cout << "\nChoose an account number: ";
	
	while (chk) {
		getline(cin, _accountNumber);
		for (size_t i = 0; i < member.size(); ++i) {
			if (strcmp(member[i].accountNumber, _accountNumber.c_str()) == 0) {
				cout << "\nAccount number \"" << _accountNumber << "\" has been used. Please choose another one: ";
				break;
			}
			else {
				chk = false;
				break;
			}
		}

		if (member.size() == 0)
			break;
	}

	cout << "\nChoose a password: ";
	getline(cin, _password);
	cout << "\nRegistration Completed!\n";

	strcpy_s(newMember.accountNumber, _accountNumber.c_str());
	strcpy_s(newMember.password, _password.c_str());
	strcpy_s(newMember.IDNumber, _IDNumber.c_str());
	strcpy_s(newMember.name, _name.c_str());
	member.push_back(newMember);
}

void Account::readReservationInfo(string _accountNumber) {
	fstream file("ReservationInfo.dat", ios::in | ios::out | ios::binary);
	ReservationInfo temp = { "", "", "", "" };

	if (!file) {
		fstream file1("ReservationInfo.dat", ios::out | ios::binary);
		file.open("ReservationInfo.dat", ios::in | ios::out | ios::binary);
	}

	for (int i = 0; i < userReservationInfo.size(); ++i)
		userReservationInfo.pop_back();
	for (int i = 0; i < memberReservationInfo.size(); ++i)
		memberReservationInfo.pop_back();

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(ReservationInfo))) {
		if (strcmp(temp.accountNumber, _accountNumber.c_str()) == 0)
			userReservationInfo.push_back(temp);
		else
			memberReservationInfo.push_back(temp);
	}
}

void Account::saveAllData() {
	fstream memberFile("MemberInfo.dat", ios::out | ios::binary);
	fstream reservationFile("ReservationInfo.dat", ios::out | ios::binary);

	for (size_t i = 0; i < member.size(); ++i)
		memberFile.write(reinterpret_cast<char*>(&member[i]), sizeof(MemberInfo));
	for (size_t i = 0; i < memberReservationInfo.size(); ++i)
		reservationFile.write(reinterpret_cast<char*>(&memberReservationInfo[i]), sizeof(ReservationInfo));
	for (size_t i = 0; i < userReservationInfo.size(); ++i)
		reservationFile.write(reinterpret_cast<char*>(&userReservationInfo[i]), sizeof(ReservationInfo));
}
