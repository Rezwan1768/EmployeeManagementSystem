#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "employee.h"
#include "utility.h"
#include "editemployee.h"

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

void editEmployeeInfo(const string& filePath)
{
	string id{};
	cout << "Enter employees 4 digit id: ";
	cin >> id;

	std::vector<Employee> employeeList{ storeDataInVector(filePath) };
	for (auto& e : employeeList)
	{
		if (id == e.getID())
		{
			int choice{};
			while(true)
			{
				cout << "1: Change ID\n";
				cout << "2: Change first name\n";
				cout << "3: Change last name\n";
				cout << "4: Chnage Phone number\n";
				cout << "5: Change Email\n";
				cout << "6. Clear Screen\n";
				cout << "0: Save and Exit\n\n";

				cout << "Option: ";
				string input{};
				cin >> choice;
				cout << '\n';
				switch (choice)
				{
				case 1: 
					cout << "Enter new ID: ";
					cin >> input;
					e.setID(input);
					break;
				case 2:
					cout << "Enter new first name: ";
					cin >> input;
					e.setFName(input);
					break;
				case 3: 
					cout << "Enter new last name: ";
					cin >> input;
					e.setLName(input);
					break;
				case 4: 
					cout << "Enter new phone number: ";
					cin >> input;
					e.setPhone(input);
					break;
				case 5:
					cout << "Enter new email: ";
					cin >> input;
					e.setEmail(input);
					break;
				case 6:
					system("CLS"); //Clear screen
					break;
				case 0:
					storeVectorInFile(employeeList, filePath);  //Clear old file data and fill it up with the new data
					cout << "Employee information updated.\n\n";
					return;
				}
			} 
		}
	}
	cout << "No employee exist with this ID.\n\n";
}

void removeEmployee(const string& filePath)  
{
	string id{};
	cout << "Enter employees 4 digit id: ";
	cin >> id;
	std::vector<Employee> temp{ storeDataInVector(filePath) };	//Store the data before file is cleared
	std::vector<Employee> employeeList{};
	bool matchFound{ false };
	for (const auto& e : temp)
	{
		if (id == e.getID())
		{
			matchFound = true;
			continue;
		}
		employeeList.push_back(e);
	}
	if (!matchFound)
	{
		cout << "No employee exist with this ID.\n\n";
		return;
	}
	storeVectorInFile(employeeList, filePath);  //Clear the file and store data with the employee excluded
	cout << "Employee with id: " << id << " removed from system.\n\n";
}
