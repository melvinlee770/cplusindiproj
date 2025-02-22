#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <regex> 	
#include <iomanip>

std::string UserInputIC = "00";

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

bool validateRegex(const std::string& input, const std::string& pattern) {
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

std::string formatDate(const std::string &date) {
    std::stringstream ss(date);
    int day, month, year;
    char delimiter1, delimiter2;
    
    if (!(ss >> month >> delimiter1 >> day >> delimiter2 >> year)) {
        return date; // Return original if parsing fails
    }
    
    std::ostringstream formattedDate;
    formattedDate << std::setw(2) << std::setfill('0') << month << "/"
                  << std::setw(2) << std::setfill('0') << day << "/"
                  << year;
    return formattedDate.str();
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
        record.HireDate = formatDate(record.HireDate);
        std::getline(ss, record.BirthDate, ',');
        record.BirthDate = formatDate(record.BirthDate);

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

    if (records.empty()) {
    	std::cout << "No data captured !"<<std::endl;
    	return;
    }
    
	std::string tmpIndex;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Show array index? (y/n): "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpIndex); 
		
        if (tmpIndex.empty()) {
            std::cout << "Error: Filename cannot be empty. Please enter a valid filename.\n";
            continue;
        }
        else if (!validateRegex(tmpIndex, "^[ynYN]$")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered

	if(tmpIndex == "y" || tmpIndex == "Y") {
		std::cout << "======================================================================================================================\n";
   		std::cout << std::left 
        << std::setw(8)  << "Idx"
		<< std::setw(11) << "IC"
        << std::setw(36) << "Name"
        << std::setw(16) << "Phone"
        << std::setw(16) << "Birth Date"
        << std::setw(16) << "Hired Date"
        << "Email" 
        << std::endl;
		std::cout << "======================================================================================================================\n";
		std::cout<<std::endl;
	
		for (const auto &rec : records) {
        	std::cout << std::left
            << std::setw(8)  << rec.Idx
            << std::setw(11) << rec.IC
        	<< std::setw(36) << rec.Name
            << std::setw(16) << rec.PhoneNum
            << std::setw(16) << rec.BirthDate
            << std::setw(16) << rec.HireDate
            << rec.Email  // The last column can be printed without setw if you prefer
            << std::endl;
    	}
	}
	else if (tmpIndex == "n"|| tmpIndex == "N") {
		std::cout << "======================================================================================================================\n";
   		std::cout << std::left 
		<< std::setw(11) << "IC"
        << std::setw(36) << "Name"
        << std::setw(16) << "Phone"
        << std::setw(16) << "Birth Date"
        << std::setw(16) << "Hired Date"
        << "Email" 
        << std::endl;
		std::cout << "======================================================================================================================\n";
		std::cout<<std::endl;
	
		for (const auto &rec : records) {
        	std::cout << std::left
            << std::setw(11) << rec.IC
        	<< std::setw(36) << rec.Name
            << std::setw(16) << rec.PhoneNum
            << std::setw(16) << rec.BirthDate
            << std::setw(16) << rec.HireDate
            << rec.Email  // The last column can be printed without setw if you prefer
            << std::endl;
    	}
	}
}

std::string getUserInputIC() {
	std::string tmpUserInputIC;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Please type in ic value to search for (< 10 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputIC); 
		
        if (tmpUserInputIC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputIC, R"(^.{1,9}$)")) {
            std::cout << "Input too long. Please enter data again ( < 10 chars) : \n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpUserInputIC;
}


void ICExactFound(const std::vector<Record> &records) {

std::cout << UserInputIC;
    for (const auto &rec : records) {
    	std::cout<<rec.IC;
            if (rec.IC == UserInputIC) {
                std::cout << "Exact match found:\n";
                std::cout << "Idx: " << rec.Idx << ", Name: " << rec.Name 
                          << ", Email: " << rec.Email << ", IC: " << rec.IC 
                          << ", Phone: " << rec.PhoneNum << std::endl;
				break;
            }
		
	}	
} 

void searchICTask(int userinput, const std::vector<Record> &records) {
	switch (userinput) {
		case 1:
			UserInputIC = getUserInputIC();
			break;
		case 2:
			std::cout << "helloworld\n";
			ICExactFound(records);
			break;
		case 4:
			break;
		 default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
	}
}



