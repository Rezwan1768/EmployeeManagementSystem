#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include "employee.h"
#include "utility.h"


using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

Employee enterEmployeeInfo(const string& filePath) 
{
	string id, fname, lname, phone, email;
	std::vector ids{getIds(filePath)}; //Store all the ids in a vector
	bool idExist{};
    do
    {
		idExist = false;
        cout << "4 digit ID: ";					
        cin >> id;
		for(string EmpId: ids)
		{
			if(EmpId == id)
			{
				std::cout << "Id already exist. Please enter a unique id.\n";
				idExist = true;
				break;
			}
		}
		
    } while((id.length() != 4) || idExist);
	
	cout << "First Name: ";			cin >> fname;
	cout << "Last Name: ";			cin >> lname;
	cout << "Phone: ";			    cin >> phone;
	cout << "Email: ";				cin >> email;
	return Employee(id, fname, lname, phone, email);
}

std::vector<string> getIds(const string& filePath)
{
	std::vector<string> ids{};
	ifstream myFile(filePath);
	string line{};
	std::getline(myFile, line);  //Extract the first line
	while (std::getline(myFile, line, ','))
	{
		ids.push_back(line);
		myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Igonore the rest of the line
	}
	return ids;
}

void registerEmployee(const string& filePath) 
{
	ofstream myFile(filePath, std::ios::out | std::ios::app);
	bool loop{ true };
	while (loop)
	{
		Employee e1{};
		cout << "Employees Information\n";
		e1 = enterEmployeeInfo(filePath);
        //Enter the info into the file
		myFile << e1.getID() << ',' << e1.getFName() << ',' << e1.getLName() << "," << e1.getPhone() << ',' << e1.getEmail() << '\n';
		cout << "Any more employees to register(y/n)?\n";
		char choice{};
		cin >> choice;
		if (choice != 'y' && choice != 'Y') 
			loop = false;
	}
	myFile.close();
}

void displayEmployees(const string& filePath)
{
	ifstream myFile(filePath);
	string line{};
	std::getline(myFile, line);  //Extract the first line
    if(!std::getline(myFile, line, ',') )
    {
        std::cout << "No employees registerd.\n\n";
        return;
    }

	std::cout << line << '\t';
	while (std::getline(myFile, line, ','))
	{
		cout << line << '\t';
	}
	cout << std::endl;
	myFile.close();
}

void searchEmployee(const string& filePath)  
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
			cout << "ID: " << e.getID() << '\t' << "Name: " << e.getFName() + ' ' + e.getLName() << '\t' << "Phone: " << e.getPhone() << '\t'
				<< "Email: " << e.getEmail() << "\n\n";
			return;
		}
	}
	cout << "No employee exist with this ID.\n\n";
}
