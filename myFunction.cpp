#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <regex> 	

struct Record {
    int Idx;
    std::string Name;
    std::string Email;
    std::string IC;
    std::string PhoneNum;
    std::string HireDate;
    std::string BirthDate;
};

void printHelloWorld() {	// for testing the linking of the file
    std::cout << "helloworld" << std::endl;
}

bool validateRegex(const std::string& input, const std::string pattern) {
    std::regex regexPattern(pattern);
    return std::regex_match(input, regexPattern);
}

std::string getUserInputQ1() {
	std::string tmpfilename;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Enter the CSV filename: "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpfilename); 
		
        if (tmpfilename.empty()) {
            std::cout << "Error: Filename cannot be empty. Please enter a valid filename.\n";
            continue;
        }
        
        else if (!validateRegex(tmpfilename, R"(^.+\.csv$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpfilename;
}

std::string getUserInputQ2() {
    std::string tmpdatanum;

	do {
        std::cout << "Number of rows: ";
        std::getline(std::cin, tmpdatanum); // Use getline to allow spaces in input

        if (tmpdatanum.empty()) {
            std::cout << "Error: Filename cannot be empty. Please enter a valid filename.\n";
            continue;
        }
        else if (!validateRegex(tmpdatanum, R"(^[1-9]\d*$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    
    return tmpdatanum;
}

void loadCSV(const std::string &filename, std::vector<Record> &records, int limit) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line); // Skip header
    
    int count = 0;
    while (std::getline(file, line) && count < limit) {
        std::stringstream ss(line);
        Record record;
        std::string field;
        
        std::getline(ss, field, ',');
        record.Idx = std::stoi(field);
        
        std::getline(ss, record.Name, ',');
        std::getline(ss, record.Email, ',');
        std::getline(ss, record.IC, ',');
        std::getline(ss, record.PhoneNum, ',');
        std::getline(ss, record.HireDate, ',');
        std::getline(ss, record.BirthDate, ',');

        if (count+1 == limit) { 
        	std::cout << "\nMaximum number of records reached. Ignoring addtional data from file "<< filename<<std::endl;
            std::cout << "Done! Total no. of records read in and stored in DB " << limit<< std::endl;
        }
        
        records.push_back(record);
        count++;
    }
    file.close();
}

void displayRecords(const std::vector<Record> &records) {
	
    for (const auto &rec : records) {
        std::cout << "Idx: " << rec.Idx << ", Name: " << rec.Name 
                  << ", Email: " << rec.Email << ", IC: " << rec.IC
                  << ", Phone: " << rec.PhoneNum
                  << ", HireDate: " << rec.HireDate
                  << ", BirthDate: " << rec.BirthDate << std::endl;
    }
}


