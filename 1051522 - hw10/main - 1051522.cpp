#include "Account.h"

int main() {
	bool isExit = true;
	KTVSystem* KTV=new Account;

	cout << "\nWelcome to the Cashbox Party World!\n";
	while (isExit) {
		string input;
		cout << "\n1 - Login\n2 - Registration\n3 - End\n\nEnter your choice : (1~3) : ";
		getline(cin, input);

		if (input == "1") {
			KTV->login();
			KTV->mainMenu();
		}
		else if (input == "2") {
			KTV->registration();
		}
		else if (input == "3") {
			isExit = false;
			cout << "\nThank you! Goodbye!\n\n";
		}
		else {
			cout << "\nInvalid value, please try again!\n";
			continue;
		}

		KTV->saveAllData();
	}

	system("PAUSE");
}