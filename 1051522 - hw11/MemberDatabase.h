#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H

//#include <vector> // class uses Vector to store MemberInfo objects
#include "Vector.h" // class uses Vector to store MemberInfo objects
#include "MemberInfo.h" // MemberInfo class definition

class MemberDatabase {
	public:
	MemberDatabase(); // constructor
	~MemberDatabase(); // destructor

	// determine whether account number and password match those of an Account
	bool authenticateUser(string userAccountNumber, string userPassword); // returns true if Account authentic

	bool duplicateID(string &userIDNumber); // check if userIDNumber belongs to members

	bool duplicateAccount(string &userAccountNumber); // check if userAccountNumber belongs to members

	void pushBack(MemberInfo &newMember); // add an element at the end of members

	private:
	vector< MemberInfo > members; // Vector of the Party World's members

	void loadFromMemberFile(); // loads members from the file MemberInfo.dat
	void saveToMemberFile(); // stores members into the file MemberInfo.dat
}; // end class MemberDatabase


MemberDatabase::MemberDatabase()
	:members(1) {
	loadFromMemberFile();
}

MemberDatabase::~MemberDatabase() {
	saveToMemberFile();
}

bool MemberDatabase::authenticateUser(string userAccountNumber, string userPassword) {
	for (auto &member : members)
		if (member.getAccountNumber() == userAccountNumber && member.validatePassword(userPassword))	return true;
	return false;
}

bool MemberDatabase::duplicateID(string &userIDNumber) {
	for (auto &member : members)
		if (member.getIDNumber() == userIDNumber)	return true;
	return false;
}

bool MemberDatabase::duplicateAccount(string &userAccountNumber) {
	for (auto &member : members)
		if (member.getAccountNumber() == userAccountNumber)	return true;
	return false;
}

void MemberDatabase::pushBack(MemberInfo &newMember) {
	members.push_back(newMember);
}

void MemberDatabase::loadFromMemberFile() {
	fstream file("MemberInfo.dat", ios::in | ios::binary);
	MemberInfo temp;

	if (!file) {
		fstream file("MemberInfo.dat", ios::out);
		cout << "\nCannot open MemberInfo.dat. Please try again!\n";
		return;
	}

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(MemberInfo)))
		members.push_back(temp);
}

void MemberDatabase::saveToMemberFile() {
	fstream file("MemberInfo.dat", ios::out | ios::binary);

	for (auto &member : members)
		file.write(reinterpret_cast<char*>(&member), sizeof(MemberInfo));
}

#endif