#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <regex> 	

std::vector<std::string> row;

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

void readCSV(const std::string &filename, int datanum, std::vector<std::vector<std::string>> &data) {
	 std::ifstream file(filename);
	 if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    
    std::string line;
    int rowCount = 0;
    int columnCount = 0;
    
    
   while (std::getline(file, line)) {
        std::stringstream ss;
        ss.str(line);  // Set the stringstream to process the current line
        std::string cell;
        std::vector<std::string> row;

        if (rowCount == 0) {  // Count columns from the first row
            while (std::getline(ss, cell, ',')) {
                columnCount++;
            }
            std::cout << "The CSV file has " << columnCount << " columns." << std::endl;

            // Reset the stringstream to reprocess the first row
            ss.clear();
            ss.str(line);
        }

        // Read and store the row data
        while (std::getline(ss, cell, ',')) {
            //std::cout << cell;
            row.push_back(cell);
        }
        std::cout << std::endl;
        
        if (row.size() == 7) {  // Ensure it contains exactly 7 elements
            data.push_back(row);
        } else {
            std::cerr << "Warning: Row does not have exactly 7 columns. Skipping." << std::endl;
        }

        rowCount++;

        if (rowCount >= datanum) {
            std::cout << "Maximum number of records reached. Ignoring additional data from file '" << filename << "'" << std::endl;
            std::cout << "Done! Total no. of records read in and stored in DB: " << datanum << std::endl;
            break;
        }
    }

    file.close();
}


void printStoredData(const std::vector<std::vector<std::string>> &data) {	// function print all the data
    std::cout << "\nStored Data (Structured Array):" << std::endl;
    for (const auto &record : data) {
        for (const auto &value : record) {
            std::cout << value;
        }
        std::cout << std::endl;
    }
}
