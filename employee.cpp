#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "employee.h"
#include "utility.h"


using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

Employee enterEmployeeInfo() 
{
	string id, fname, lname, phone, email;
	cout << "ID: ";					cin >> id;
	cout << "First Name: ";			cin >> fname;
	cout << "Last Name: ";			cin >> lname;
	cout << "Phone: ";			    cin >> phone;
	cout << "Email: ";				cin >> email;
	return Employee(id, fname, lname, phone, email);
}

void registerEmployee(string filePath) 
{
	ofstream myFile(filePath, std::ios::out | std::ios::app);
	bool loop{ true };
	while (loop)
	{
		Employee e1{};
		cout << "Employees Information\n";
		e1 = enterEmployeeInfo();
		myFile << e1.getID() << ',' << e1.getFName() << ',' << e1.getLName() << "," << e1.getPhone() << ',' << e1.getEmail() << '\n';
		cout << "Any more employees to register(y/n)?\n";
		char choice{};
		cin >> choice;
		if (choice != 'y' && choice != 'Y') 
			loop = false;
	}
	myFile.close();
}

void displayEmployees(string filePath)
{
	ifstream myFile(filePath);
	string line{};
    if(!std::getline(myFile, line, ','))
    {
        std::cout << "No employees registerd.\n";
        return;
    }
	while (std::getline(myFile, line, '\n'))
	{
		cout << std::left;
		cout << std::setw(20) << line << '\t';
	}
	cout << '\n';
	myFile.close();
}

void searchEmployee(string filePath)  
{
	string id{};
	cout << "Enter employees 4 digit id: ";
	cin >> id;

	std::vector<Employee> employeeList{ storeDataInVector(filePath) };
	for (Employee e : employeeList)
	{
		if (id == e.getID())
		{
			cout << "Employ found! Here is the employees information.\n";
			cout << "ID: " << e.getID() << '\t' << "Name: " << e.getFName() << '\t ' << e.getLName() << '\t' << "Phone: " << e.getPhone() << '\t'
				<< "Email: " << e.getEmail() << '\n';
			return;
		}
	}
	cout << "No employee exist with this ID.\n";
}
