#include "User.h"

class WithDraw {
	public:
	WithDraw() :bills(500) {};
	void doWithDraw(User& user);

	private:
	int bills;
};

void WithDraw::doWithDraw(User& user) {
	int choice = 0, money[6] = { 0, 20, 40, 60, 100, 200 };

	while (cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\nChoose a withdrawal option (1-6): ") {
		cin >> choice;

		if (choice > 6)
			cout << "invalid value, please try again!\n";
		else if (choice == 6)
			return;
		else if (money[choice] > user.getAccount().availableBalance)
			cout << "\nYou have only $" << user.getAccount().availableBalance << " to withdraw, please choose a smaller amount!\n";
		else if (money[choice] > (bills * 20))
			cout << "\nSorry, there is only $" << bills * 20 << " to be withdrew, please choose a smaller amount!\n";
		else
			break;	
	}

	bills -= money[choice] / 20;
	int temp1 = user.getAccount().availableBalance - money[choice];
	int temp2 = user.getAccount().totalBalance - money[choice];
	user.setAccount(temp1, temp2);
		
	cout << "\nPlease take your cash from the cash dispenser.\n";
}