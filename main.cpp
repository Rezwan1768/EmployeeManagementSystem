#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

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
				myFile << "ID,First Name,Last Name,Phone,Email\n";
				cout << filePath << " created.\n";
				break;
			}
			else
			{
				cout << "Would you like to exit?(y/n): ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
					exit(0); //Terminate program
			}
		}
		else
		{
			readFile.close();
			return filePath;
		}
	}
}

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

void registerEmployee(string filePath) //Fix issue with empty file
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

//Function that colllects the data from the csv file and stores it in a avector
std::vector<Employee> storeDataInVector(string filePath)
{
	std::vector<Employee> employeeData{};
	std::ifstream myFile(filePath);
	string line{};
	std::getline(myFile, line, '\n');  //Extract and ignore the first row

	while (std::getline(myFile, line, '\n')) //Extract whole line 
	{
		std::stringstream sstream(line);
		string word;
		std::stringstream words;

		while (std::getline(sstream, word, ','))  //Extract each csv from line
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

void storeVectorInFile(const std::vector<Employee>& employeeList, string filePath)
{
	ofstream myFile(filePath);
	myFile << "ID,First Name,Last Name,Phone,Email\n";
	for (const Employee& e : employeeList)
	{
		myFile << e.getID() << ',' << e.getFName() << ',' << e.getLName() << ',' << e.getPhone() << ',' << e.getEmail() << '\n';
	}
	myFile.close();
}

void editEmployeeInfo(string filePath)
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
				cout << "0: Save and Exit\n";
				string input{};
				cin >> choice;
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
				case 0:
					storeVectorInFile(employeeList, filePath);
					cout << "Employee information updated.\n";
					return;
				}
			} 
		}
	}
	cout << "No employee exist with this ID.\n";
}

void removeEmployee(string filePath)  
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
		cout << "No employee exist with this ID.\n";
		return;
	}
	storeVectorInFile(employeeList, filePath);
	cout << "Employee with id: " << id << " removed from system.\n";
}

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
		cout << '\n';
		
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
