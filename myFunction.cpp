#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <regex> 	

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


