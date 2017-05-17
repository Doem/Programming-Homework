#ifndef KTV_H
#define KTV_H
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

struct MemberInfo {
	char accountNumber[24];	// �b��
	char password[24];		// �K�X
	char IDNumber[12];		// �����Ҧr��
	char name[8];			// �m�W
};

struct ReservationInfo {
	char accountNumber[24];	// �b��
	char branch[24];		// ����
	char date[12];			// �w�����
	char hour[4];			// �w���p��
	char roomType[16];		// �]�[����
	int customerNumber;		// ���O�H
};

class KTVSystem {
	public:
	virtual void login() = 0;
	virtual void saveAllData() = 0;
	virtual void registration() = 0;
	void mainMenu();
	bool addReservation();
	bool editReservation();
	void setUser(MemberInfo&);

	protected:
	MemberInfo nowUser;
	vector<ReservationInfo> userReservationInfo;
};
#endif KTV_H