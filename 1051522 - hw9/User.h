#ifndef USER_H
#define USER_H
//#define Write
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

struct Account {
	char accountNumber[40];
	char PIN[20];
	unsigned int availableBalance;
	unsigned int totalBalance;
};

class User {
	public:
	User();
 	bool login();
	int mainMenu();
	bool saveAccount();
	bool readAccount(string, string);
	void setAccount(int, int);
	Account getAccount() { return account; };

	protected:
	int count;
	Account account;
};

User::User()
	:count(0), account({ "", "", 0, 0 }) {
}

int User::mainMenu() {
	int choice;
	cout << "\nMain menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\nEnter a choice: ";
	cin >> choice;
	return choice;
}

bool User::login() {
	string accountNumber, PIN;

	cout << "\nWelcome!\n\nPlease enter your account number: ";
	cin >> accountNumber;
	cout << "\nEnter your PIN: ";
	cin >> PIN;

	return (readAccount(accountNumber, PIN));
}

bool User::readAccount(string _accountNumber, string _PIN) {
	fstream file("account.dat", ios::in | ios::out | ios::binary);

	if (!file) {
		fstream file("account.dat", ios::out | ios::binary);
#ifdef Write
		Account p1 = { "11111111111111111111", "222222222222222222", 1000, 1200 }, p2 = { "98765", "56789", 200, 200 };

		file.write(reinterpret_cast<char*>(&p1), sizeof(Account));
		file.write(reinterpret_cast<char*>(&p2), sizeof(Account));
#endif
		cout << "\nCannot open account.dat, please try again!\n";
		return false;
	}


	while (file.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
		if (strcmp(account.accountNumber, _accountNumber.c_str()) == 0 && strcmp(account.PIN , _PIN.c_str()) == 0)	return true;
		++count;
	}
	return false;
}

bool User::saveAccount() {
	fstream file("account.dat", ios::in | ios::out | ios::binary);

	if (!file) {
		fstream file("account.dat", ios::out | ios::binary);
		cout << "\nCannot open account.dat, please try again!\n";
		return false;
	}

	account.availableBalance = account.totalBalance;
	file.seekp(sizeof(Account) * count);
	file.write(reinterpret_cast<char*>(&account), sizeof(Account));
}

void User::setAccount(int _availableBalance, int _totalBalance) {
	account.availableBalance = _availableBalance;
	account.totalBalance = _totalBalance;
}
#endif