#ifndef MY_FUNCTION_H
#define MY_FUCNTION_H
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <iostream>

extern std::string UserInputIC;

struct Record {
    int Idx;
    std::string Name;
    std::string Email;
    std::string IC;
    std::string PhoneNum;
    std::string HireDate;
    std::string BirthDate;
};

bool validateRegex(const std::string& input, const std::string& pattern);

void printHelloWorld();

void loadCSV(const std::string &filename, std::vector<Record> &records, int limit);
void displayRecords(const std::vector<Record> &records);
std::string formatDate(const std::string &date);
             
std::string getUserInputQ1();
std::string getUserInputQ2();

void searchICTask(int userinput, const std::vector<Record> &records);
std::string getUserInputIC();
void ICExactFound(const std::vector<Record> &records);
void ICPartialFound(const std::vector<Record> &records);

#endif

