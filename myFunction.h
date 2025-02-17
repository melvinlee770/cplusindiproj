#ifndef MY_FUNCTiON_H
#define MY_FUCNTION_H
#include <string>
#include <regex>

void printHelloWorld();
void readCSV(const std::string &filename, int datanum);
void getUserInputQ2(std::string &filename, int &datanum);

std::string trim(const std::string &str);
std::string validateInput(const std::string &prompt, const std::regex &pattern, const std::string &errorMessage);

#endif

