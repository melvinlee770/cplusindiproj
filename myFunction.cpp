#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <limits> 

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

std::string validateInput(const std::string &prompt, const std::regex &pattern, const std::string &errorMessage) {
    std::string input;
    bool firstAttempt = true;
    while (true) {
        std::cout << prompt;
        std::cin.clear(); 
        
        if (std::cin.peek() == '\n' && firstAttempt) {  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //std::cout << "marking a"<<std::endl;
            firstAttempt = false;
        }
        
        getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "Error: Input cannot be empty.\n";
            continue;
        }

        if (regex_match(input, pattern)) {
        	//std::cout << "marking b"<<std::endl;
        	firstAttempt = true;
            return input; // Valid input
        } else {
            std::cout << errorMessage << std::endl;
        }
    }
}

void printHelloWorld() {	// for testing the linking of the file
    std::cout << "helloworld" << std::endl;
}

void getUserInputQ2(std::string &filename, int &datanum){

    std::regex filenamePattern(R"(^\S[\w\s-]*\.csv$)");
 	std::regex numberPattern(R"(^[1-9][0-9]*$)");

    
    filename = validateInput("Enter the CSV filename (e.g. data.csv): ", 
    						filenamePattern, 
    						"INPUT_ERROR");

    std::string tmpdatanum = validateInput("Enter the number of rows to display (positive integer): ", 
                                  numberPattern, 
                                  "INPUT_ERROR");
   datanum = stoi(tmpdatanum);
}

void readCSV(const std::string &filename, int datanum) {
	 std::ifstream file(filename);
	 if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    
    std::string line;
    int rowCount = 0;
    
    while (std::getline(file, line)) {
        if (rowCount >= datanum) {
            std::cout << "Display limit reached. Stopping output.\n";
            break;
        }
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        for (const auto &data : row) {
            std::cout <<" "<<data<<" ";
        }
        
        //std::cout<<row[3]<<std::endl;
        std::cout << std::endl;
        rowCount++;
    }

    file.close();
}


