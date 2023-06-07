#ifndef UTILITY_H
#define UTILITY_H

string getFile();
std::vector<Employee> storeDataInVector(const string& filePath);
void storeVectorInFile(const std::vector<Employee>& employeeList, const string& filePath);
#endif