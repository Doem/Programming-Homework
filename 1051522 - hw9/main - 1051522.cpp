#include <iostream>
#include "ATM.h"
#include "User.h"
using namespace std;

int main() {
	ATM atm;
	User user;
	int choice;

	while (1) {
		if (user.login()) {
			while (choice = user.mainMenu()) {
				if (choice == 1)
					atm.viewBalance.doViewBalance(user);
				else if (choice == 2)
					atm.withDraw.doWithDraw(user);
				else if (choice == 3)
					atm.dePosit.doDePosit(user);
				else if (choice == 4) {
					user.saveAccount();
					cout << "\nExiting the system...\n\nThank you! Goodbye!\n";
					break;
				}
				else
					cout << "\nInvalid value, please try again!" << endl;
			}
		}
		else {
			cout << "\nWrong accountNumber or PIN, please check them again!\n";
		}
	}
	return 0;
}