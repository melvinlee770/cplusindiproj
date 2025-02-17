#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void printHelloWorld() {
    std::cout << "helloworld" << std::endl;
}

void readCSV(const std::string &filename) {
	 std::ifstream file(filename);
	 if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        for (const auto &data : row) {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }

    file.close();
}
