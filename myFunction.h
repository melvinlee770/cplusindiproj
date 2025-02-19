#ifndef MY_FUNCTiON_H
#define MY_FUCNTION_H
#include <string>
#include <regex>
#include <vector>

//extern std::vector<std::vector<std::string>> data;

bool validateRegex(const std::string& input, const std::string& pattern);

void printHelloWorld();
void readCSV(const std::string &filename, int datanum, std::vector<std::vector<std::string>> &data);
std::string getUserInputQ1();
std::string getUserInputQ2();

void printStoredData(const std::vector<std::vector<std::string>> &data);

#endif

