#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "employee.h"
#include "utility.h"

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

string getFile()
{
	ifstream readFile;
	string filePath{};
	while (true)
	{
		cout << "Enter file path: ";
		cin >> filePath;
		readFile.open(filePath);
		if (!readFile)  //If file doesn't exist
		{
			cout << "File path doesn't exist! \n";
			cout << "Would you like to create a new file with the specified path?(y/n): ";
			char choice{};
			cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				std::ofstream myFile(filePath);  //Create a new file
				myFile << "ID,First Name,Last Name,Phone,Email\n";  //Imclude these column heading
				cout << filePath << " created.\n";
			}
			else
			{
				cout << "Would you like to exit?(y/n): ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
					exit(0); //Terminate program
			}
            readFile.close();
			return filePath;
		}
		else
		{
			readFile.seekg(0, std::ios::end); // Move the file pointer to the end
			if (readFile.tellg() == 0) // If the position is 0, then file is empty
			{
    			std::ofstream myFile(filePath);
				myFile << "ID,First Name,Last Name,Phone,Email\n";  //Imclude these column heading
			}
			readFile.close();
			return filePath;
		}
	}
}

//Function that colllects the data from the csv file and stores it in a avector
std::vector<Employee> storeDataInVector(string filePath)
{
	std::vector<Employee> employeeData{};
	std::ifstream myFile(filePath);
	string line{};
	std::getline(myFile, line, '\n');  //Extract and ignore the first row

	while (std::getline(myFile, line, '\n')) //Extract whole line 
	{
		std::stringstream sstream(line); //Store it in a sstream object
		string word;
		std::stringstream words;  

		while (std::getline(sstream, word, ','))  //Extract each csv from line, without the comma
		{
			words << word << ' ';
		}
		
		string id, fname, lname, phone, email;
		words >> id >> fname >> lname >> phone >> email;
		Employee e1(id, fname, lname, phone, email);
		employeeData.push_back(e1);
		words.str("");
	}
	myFile.close();
	return employeeData;
}

void storeVectorInFile(const std::vector<Employee>& employeeList, string filePath)
{
	ofstream myFile(filePath);
	myFile << "ID,First Name,Last Name,Phone,Email\n"; //Imclude these column heading first
	for (const Employee& e : employeeList)
	{
		myFile << e.getID() << ',' << e.getFName() << ',' << e.getLName() << ',' << e.getPhone() << ',' << e.getEmail() << '\n';
	}
	myFile.close();
}