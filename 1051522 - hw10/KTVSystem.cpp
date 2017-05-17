#include "KTVSystem.h"

char branches[16][25] = { "", "Taipei Dunhua South", "Taipei SOGO", "Taipei Songjiang", "Taipei Nanjing", "Taipei Linsen", "Taipei Zhonghua New", "Banqiao Guanqian", "Yonghe Lehua", "Taoyuan Zhonghua", "Zhongli Zhongyang", "Hsinchu Beida", "Taichung Ziyou", "Chiayi Ren'ai", "Tainan Ximen", "Kaohsiung Zhonghua New" };

void KTVSystem::mainMenu() {
	string choice;

	while (true) {
		cout << "\n1 - Make Reservation\n2 - Reservation Enquiry / Canceling\n3 - End\n\nEnter your choice: (1~3): ";
		getline(cin, choice);

		if (choice == "1")
			addReservation();
		else if (choice == "2")
			editReservation();
		else if (choice == "3")
			break;
		else
			cout << "\nInvalid value, please try again!\n";
	}
}

bool KTVSystem::addReservation() {
	int temp;
	ReservationInfo newReservationInfo;
	string _branch, _date, _hour, _roomType, _customerNumber;

	while (true) {
		stringstream ss;

		cout << endl;
		for (int i = 1; i < 16; ++i)
			cout << setw(2) << i << ". " << branches[i] << endl;
		cout << "\nEnter your choice: ";
		getline(cin, _branch);

		ss << _branch;
		ss >> temp;
		if (temp >= 1 && temp <= 15) {
			strcpy_s(newReservationInfo.branch, branches[temp]);
			break;
		}
		else
			cout << "\nInvalid value, please try again!\n";
	}

	cout << "\nEnter date (yyyy-mm-dd): ";
	getline(cin, _date);
	strcpy_s(newReservationInfo.date, _date.c_str());

	while (true) {
		stringstream ss;

		cout << "\nEnter hour (0~23): ";
		getline(cin, _hour);

		ss << _hour;
		ss >> temp;
		if (temp >= 0 && temp <= 23) {
			strcpy_s(newReservationInfo.hour, _hour.c_str());
			break;
		}
		else
			cout << "\nInvalid value, please try again!\n";
	}

	while (true) {
		stringstream ss;

		cout << "\nEnter the number of customers (1~30): ";
		getline(cin, _customerNumber);

		ss << _customerNumber;
		ss >> temp;
		if (temp >= 1 && temp <= 30) {
			newReservationInfo.customerNumber = temp;
			break;
		}
		else
			cout << "\nInvalid value, please try again!\n";
	}

	while (true) {
		stringstream ss;

		cout << "\n1. Standard Room\n2. Party Room\n\nEnter your choice : (1~2) : ";
		getline(cin, _roomType);

		if (_roomType == "1") {
			strcpy_s(newReservationInfo.roomType, "Standard");
			break;
		}
		else if (_roomType == "2") {
			strcpy_s(newReservationInfo.roomType, "Party");
			break;
		}
		else
			cout << "\nInvalid value, please try again!\n";
	}

	cout << "\nReservation Completed!\n";
	strcpy_s(newReservationInfo.accountNumber, nowUser.accountNumber);
	userReservationInfo.push_back(newReservationInfo);
	return true;
}

bool KTVSystem::editReservation() {
	int temp;
	string choice;
	stringstream ss; 

	if (userReservationInfo.size() == 0) {
		cout << "\nNo reservation information!\n";
		return false;
	}

	cout << endl << right << setw(17) << "Account Number"
		<< setw(26) << "Branch"
		<< setw(14) << "Date"
		<< setw(8) << "Hour"
		<< setw(13) << "Room Type"
		<< setw(19) << "No of Customers" << endl;
	for (size_t i = 1; i <= userReservationInfo.size(); ++i)
		cout << i << "." << right << setw(17 - i / 10 - 2) << userReservationInfo[i - 1].accountNumber
		<< setw(26) << userReservationInfo[i - 1].branch
		<< setw(14) << userReservationInfo[i - 1].date
		<< setw(8) << userReservationInfo[i - 1].hour
		<< setw(13) << userReservationInfo[i - 1].roomType
		<< setw(19) << userReservationInfo[i - 1].customerNumber << endl;

	while (true) {
		cout << "\nChoose a reservation to cancel (0: keep all reservations): ";
		getline(cin, choice);

		ss << choice;
		ss >> temp;
		if (temp == 0)
			return false;
		else if (temp > 0 && temp < userReservationInfo.size()) {
			userReservationInfo.erase(userReservationInfo.begin() + temp - 1);
			cout << "\nReservation Completed!\n";
			return true;
		}
		else
			cout << "\nInvalid value, please try again!\n";
	}
}

void KTVSystem::setUser(MemberInfo& member) {
	strcpy_s(nowUser.accountNumber, member.accountNumber);
	strcpy_s(nowUser.password, member.password);
	strcpy_s(nowUser.IDNumber, member.IDNumber);
	strcpy_s(nowUser.name, member.name);
}