#include <iostream>
#include <fstream>
#include <string>

#include <vector>

#include "employee.h"
#include "utility.h"
#include "editinfo.h"

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;


int main()
{
	string filePath{ getFile() };
	int option{};
	do {
		cout << "1: Register Employee(s)\n";
		cout << "2: Display all Employees\n";
		cout << "3: Search Employee\n";
		cout << "4: Edit Employee Information\n";
		cout << "5: Remove Employee\n";
		cout << "0: Exit\n\n";
		
		cout << "Enter option: ";  
		cin >> option;
		
		switch (option)
		{
		case 0:
			break;
		case 1: 
			registerEmployee(filePath);
			break;
		case 2: 
			displayEmployees(filePath);
			break;
		case 3:
			searchEmployee(filePath);
			cout << '\n';
			break;
		case 4: 
			editEmployeeInfo(filePath);
			break;
		case 5:
			removeEmployee(filePath);
			break;
		default:
			cout << "Inavalid option\n";
		}
	} while (option != 0);
}
