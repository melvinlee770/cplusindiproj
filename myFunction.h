#ifndef MY_FUNCTION_H
#define MY_FUCNTION_H
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <iostream>

extern int captureCount;

extern std::string userInputIC;
extern std::string userInputName;
extern std::string userInputEmail;
extern std::string userInputPhone;

extern std::string userUpdata;

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
void searchNameTask(int userinput, const std::vector<Record> &records);
void searchEmailTask(int userinput, const std::vector<Record> &records);
void searchPhoneTask(int userinput, const std::vector<Record> &records);

void insertNewRecord(std::vector<Record>& records);

void updataRecord(std::vector<Record>& records);

void deleteRecord(std::vector<Record>& records);

#endif

