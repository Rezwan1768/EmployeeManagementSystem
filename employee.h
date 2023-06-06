#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using std::string;

class Employee
{
	string m_id{};
	string m_fName{};
	string m_lName{};
	string m_phone{};
	string m_email{};

public:
	Employee(string id, string fname, string lname, string phone, string email) :
		m_id{ id }, m_fName{ fname }, m_lName{ lname }, m_phone{ phone }, m_email {email}{};

	Employee() {};

	string getID() const { return m_id; }
	string getFName() const { return m_fName; }
	string getLName() const { return m_lName; }
	string getPhone() const { return m_phone; }
	string getEmail() const { return m_email; }
	
	void setID(string id) { m_id = id; }
	void setFName(string fName) { m_fName = fName; }
	void setLName(string lName) { m_lName = lName; }
	void setPhone(string phone) { m_phone = phone; }
	void setEmail(string email) { m_email = email; }
};

Employee enterEmployeeInfo();
void registerEmployee(string filePath);
void displayEmployees(string filePath);
void searchEmployee(string filePath);
#endif