#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

void printHelloWorld() {	// for testing the linking of the file
    std::cout << "helloworld" << std::endl;
}

void getUserInputQ2(std::string &filename, int &datanum){
    std::cout << "Enter the CSV filename: ";
    std::cin >> filename;

    std::cout << "Enter the number of rows to display: ";
    std::cin >> datanum;
    std::cout<<std::endl;

    // Ensure displayLimit is positive
    if (datanum <= 0) {
        std::cout << "Invalid input! Setting display limit to 1.\n";
        datanum = 1;
    }
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
