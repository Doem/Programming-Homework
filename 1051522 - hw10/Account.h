#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "KTVSystem.h"
using namespace std;

class Account :public KTVSystem{
	public:
	Account();
	string getName(int);
	string getIDNumber(int);
	string getPassword(int);
	string getAccountNumber(int);
	void login();
	void registration();
	void readReservationInfo(string);
	void saveAllData();

	private:
	vector<MemberInfo> member;
	vector<ReservationInfo> memberReservationInfo;
};
#endif ACCOUNT_H