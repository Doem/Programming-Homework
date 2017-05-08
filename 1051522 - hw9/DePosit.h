#include "User.h"

class DePosit {
	public:
	void doDePosit(User& user);
};

void DePosit::doDePosit(User& user) {
	int money;
	
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> money;

	if (money == 0)
		return;
	else {
		cout << "\nPlease insert a deposit envelope containing $" << money << " in the deposit slot.\n";
		cout << "\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";
		int temp = user.getAccount().totalBalance + money;
		user.setAccount(user.getAccount().availableBalance, temp);
	}
}