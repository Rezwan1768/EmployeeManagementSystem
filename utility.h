#ifndef UTILITY_H
#define UTILITY_H

string getFile();
std::vector<Employee> storeDataInVector(string filePath);
void storeVectorInFile(const std::vector<Employee>& employeeList, string filePath);
#endif