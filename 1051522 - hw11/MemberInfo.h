#ifndef MEMBERINFO_H
#define MEMBERINFO_H

#include <string>
using std::string;

class MemberInfo {
	public:
	MemberInfo(string theAccountNumber = "", string thePassword = "", string theIDNumber = "", string theName = "") {};

	void setAccountNumber(string theAccountNumber);
	string getAccountNumber() const;

	void setPassword(string thePassword);
	string getPassword() const;

	void setIDNumber(string theIDNumber);
	string getIDNumber() const;

	void setName(string theName);
	string getName() const;

	bool validatePassword(string userPassword) const; // is user-specified password correct?
	private:
	char accountNumber[24]; // account number
	char password[24];      // password
	char IDNumber[12];      // ID number
	char name[8];           // name
};

void MemberInfo::setAccountNumber(string theAccountNumber) {
	strcpy_s(accountNumber, theAccountNumber.c_str());
}

string MemberInfo::getAccountNumber() const {
	return string(accountNumber);
}

void MemberInfo::setPassword(string thePassword) {
	strcpy_s(password, thePassword.c_str());
}

string MemberInfo::getPassword() const {
	return string(password);
}

void MemberInfo::setIDNumber(string theIDNumber) {
	strcpy_s(IDNumber, theIDNumber.c_str());
}

string MemberInfo::getIDNumber() const {
	return string(IDNumber);
}

void MemberInfo::setName(string theName) {
	strcpy_s(name, theName.c_str());
}

string MemberInfo::getName() const {
	return string(name);
}

bool MemberInfo::validatePassword(string userPassword) const {
	return (string(password) == userPassword);
}
#endif