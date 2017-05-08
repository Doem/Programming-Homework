#include "User.h"

class ViewBalance {
	public:
	void doViewBalance(User&);
};

void ViewBalance::doViewBalance(User& user) {
	cout << "\nBalance Information:\n - Available balance: $";
	cout << user.getAccount().availableBalance;
	cout << ".0\n - Total balance:     $";
	cout << user.getAccount().totalBalance << ".0" << endl;
}