#ifndef MY_FUNCTiON_H
#define MY_FUCNTION_H
#include <string>
#include <regex>

bool validateRegex(const std::string& input, const std::string& pattern);

void printHelloWorld();
bool checkEmpty(const std::string& input);
void readCSV(const std::string &filename, int datanum);
std::string getUserInputQ1();
std::string getUserInputQ2();

#endif

