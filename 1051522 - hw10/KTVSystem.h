#ifndef KTV_H
#define KTV_H
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

struct MemberInfo {
	char accountNumber[24];	// 帳號
	char password[24];		// 密碼
	char IDNumber[12];		// 身分證字號
	char name[8];			// 姓名
};

struct ReservationInfo {
	char accountNumber[24];	// 帳號
	char branch[24];		// 分店
	char date[12];			// 預約日期
	char hour[4];			// 預約小時
	char roomType[16];		// 包廂類型
	int customerNumber;		// 消費人
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