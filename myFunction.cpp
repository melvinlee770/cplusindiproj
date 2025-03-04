#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <regex> 	
#include <iomanip>

#include <algorithm>
#include <cctype>
#include <locale>

int captureCount = 1; 

std::string userInputIC = "00";
std::string userInputName = "SAMPLE_NAME";
std::string userInputEmail = "SAMPLE_EMAIL";
std::string userInputPhone = "SAMPLE_PHONE";

struct Record {
    int Idx;
    std::string Name;
    std::string Email;
    std::string IC;
    std::string PhoneNum;
    std::string HireDate;
    std::string BirthDate;
};

std::string trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
        start++;
    
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    
    return std::string(start, end + 1);
}

void printHelloWorld() {	// for testing the linking of the file
    std::cout << "helloworld" << std::endl;
}

bool validateRegex(const std::string& input, const std::string& pattern) {
    std::regex regexPattern(pattern);
    return std::regex_match(input, regexPattern);
}

std::string getUserInputQ1() {
	std::string tmpfilename;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

/*
void loadCSV(const std::string &filename, std::vector<Record> &records, int limit) {
    std::ifstream file(filename);
	std::string line;
        
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    
    if (captureCount > 1) {
        std::cerr << "You already captured the file" << std::endl;
        return;
    }
    
    // Read the header line.
    if (!std::getline(file, line)) {
        std::cerr << "Error reading header." << std::endl;
        return;
    }
    
    // Split header into tokens.
    std::istringstream headerStream(line);
    std::string token;
    std::vector<std::string> headerTokens;
    while (std::getline(headerStream, token, ',')) {
        headerTokens.push_back(trim(token));
    }
    
    // Determine if the CSV file has an index column in the first column.
    bool hasIndex = false;
    if (!headerTokens.empty()) {
        std::string firstToken = headerTokens[0];
        if (firstToken == "Idx") {
            hasIndex = true;
        }
    }
    
    int count = 0;
    while (std::getline(file, line) && count < limit) {
        std::stringstream ss(line);
        Record record;
        std::string field;
        
        if (hasIndex) {
            std::getline(ss, field, ','); // read and ignore the index field
            record.Idx = count + 1; // assign our own index
        } else {
            record.Idx = count + 1;
        }
        
        // Read the remaining fields.
        std::getline(ss, record.Name, ',');
        std::getline(ss, record.Email, ',');
        std::getline(ss, record.IC, ',');
        std::getline(ss, record.PhoneNum, ',');
        std::getline(ss, record.HireDate, ',');
        record.HireDate = formatDate(record.HireDate);
        std::getline(ss, record.BirthDate, ',');
        record.BirthDate = formatDate(record.BirthDate);
		std::cout << count << std::endl;
        if (count + 1> limit) {
            std::cout << "\nMaximum number of records reached. Ignoring additional data from file " << filename << std::endl;
            std::cout << "Done! Total no. of records read in and stored in DB " << limit << std::endl;
            break;
        }
        records.push_back(record);
        count++;
        captureCount++;
    }
    std::cout << "Done! Total no. of records read in and stored in DB " << count << std::endl;
    file.close();
}
*/


void loadCSV(const std::string &filename, std::vector<Record> &records, int limit) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    if (captureCount > 1) {
        std::cerr << "You already captured the file" << std::endl;
        return;
    }

    // Read and process header
    if (!std::getline(file, line)) {
        std::cerr << "Error reading header." << std::endl;
        return;
    }

    std::istringstream headerStream(line);
    std::vector<std::string> headerTokens;
    std::string token;

    while (std::getline(headerStream, token, ',')) {
        headerTokens.push_back(trim(token));
    }

    bool hasIndex = !headerTokens.empty() && headerTokens[0] == "Idx";

    int count = 0;
    while (std::getline(file, line)) {
        if (count >= limit) {
        	std::cout << "\nMaximum number of records reached. Ignoring additional data from file " << filename << std::endl;
            std::cout << "Done! Total no. of records read in and stored in DB " << limit << std::endl;
            file.close();
            return; // Stops function immediately
        }

        std::stringstream ss(line);
        Record record;
        std::string field;

        if (hasIndex) {
            std::getline(ss, field, ',');
            try {
                record.Idx = std::stoi(field);
            } catch (...) {
                record.Idx = count + 1;
            }
        } else {
            record.Idx = count + 1;
        }

        std::getline(ss, record.Name, ',');
        std::getline(ss, record.Email, ',');
        std::getline(ss, record.IC, ',');
        std::getline(ss, record.PhoneNum, ',');
        std::getline(ss, record.HireDate, ',');
        record.HireDate = formatDate(record.HireDate);
        std::getline(ss, record.BirthDate, ',');
        record.BirthDate = formatDate(record.BirthDate);

        records.push_back(record);
        count++;
    }

    std::cout << "Done! Total no. of records read in and stored in DB: " << count << std::endl;
    captureCount++;  // Increment once after processing

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
            std::cout << "Error: Filename cannot be empty. Please enter a valid input\n";
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
        std::cout << "Please type in ic to search for (< 10 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputIC); 
		
        if (tmpUserInputIC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputIC,R"(^[A-Za-z0-9]{1,9}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpUserInputIC;
}


void ICExactFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
	//std::cout << userInputIC;
    for (const auto &rec : records) {
    	//std::cout<<rec.IC;
		if (rec.IC == userInputIC) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
		}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;
	if (!found) {
		std::cout << "No record found with IC" << userInputIC << std::endl;
	}
} 

void ICPartialFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
    for (const auto &rec : records) {
    	//std::cout<<rec.IC;
		if (rec.IC.find(userInputIC) != std::string::npos) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;
	if (!found) {
		std::cout << "No record found with IC" << userInputIC << std::endl;
    }
}       

void searchICTask(int userinput, const std::vector<Record> &records) {
	switch (userinput) {
		case 1:
			userInputIC = getUserInputIC();
			break;
		case 2:
			ICExactFound(records);
			break;
		case 3:
			ICPartialFound(records);
			break;
		case 4:
			break;
		 default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
	}
}

std::string getUserInputName() {
	std::string tmpUserInputName;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Please type in name to search for (< 35 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputName); 
		
        if (tmpUserInputName.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid name.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputName, R"(^(?=.{1,35}$)(?=.*\S)[A-Za-z\s'-]+$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpUserInputName;
}


void NameExactFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
	std::string tmpNameLower = userInputName;
    std::transform(tmpNameLower.begin(), tmpNameLower.end(), tmpNameLower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
                   
    for (const auto &rec : records) {
    	std::string tmpRecNameLower = rec.Name;
		std::transform(tmpRecNameLower.begin(), tmpRecNameLower.end(), tmpRecNameLower.begin(),
                       [](unsigned char c){ return std::tolower(c); });
                       
		if (tmpRecNameLower == tmpNameLower ) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;
	if (!found) {
		std::cout << "No record found with name" << userInputName << std::endl;
   	}
} 


void NamePartialFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
	std::string tmpNameLower = userInputName;
    std::transform(tmpNameLower.begin(), tmpNameLower.end(), tmpNameLower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
                   
    for (const auto &rec : records) {
    	std::string tmpRecNameLower = rec.Name;
		std::transform(tmpRecNameLower.begin(), tmpRecNameLower.end(), tmpRecNameLower.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    	
		if (tmpRecNameLower.find(tmpNameLower) != std::string::npos) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;
	if (!found) {
		std::cout << "No record found with name" << userInputName << std::endl;
    }
}


void searchNameTask(int userinput, const std::vector<Record> &records) {
	switch (userinput) {
		case 1:
			userInputName = getUserInputName();
			break;
		case 2:
			NameExactFound(records);
			break;
		case 3:
			NamePartialFound(records);
			break;
		case 4:
			break;
		 default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
	}
}


std::string getUserInputEmail() {
	std::string tmpUserInputEmail;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Please type in email to search for (< 35 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputEmail); 
		
        if (tmpUserInputEmail.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid email.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputEmail, R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
      
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpUserInputEmail;
}


void EmailExactFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
    for (const auto &rec : records) {
		if (rec.Email == userInputEmail ) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;	
	if (!found) {
		std::cout << "No record found with email: " << userInputEmail << std::endl;
   	}
} 


void EmailPartialFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
	std::string tmpEmailLower = userInputEmail;
    std::transform(tmpEmailLower.begin(), tmpEmailLower.end(), tmpEmailLower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
                   
    for (const auto &rec : records) {
    	std::string tmpRecEmailLower = rec.Email;
		std::transform(tmpRecEmailLower.begin(), tmpRecEmailLower.end(), tmpRecEmailLower.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    	
		if (tmpRecEmailLower.find(tmpEmailLower) != std::string::npos) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}
	std::cout <<"\n" << matchCount << " records found"<<std::endl;	
	if (!found) {
		std::cout << "No record found with email: " << userInputEmail << std::endl;
    }
}


void searchEmailTask(int userinput, const std::vector<Record> &records) {
	switch (userinput) {
		case 1:
			userInputEmail = getUserInputEmail();
			break;
		case 2:
			EmailExactFound(records);
			break;
		case 3:
			EmailPartialFound(records);
			break;
		case 4:
			break;
		 default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
	}
}


std::string getUserInputPhone() {
	std::string tmpUserInputPhone;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Please type in phone number to search for (< 15 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputPhone); 
		
        if (tmpUserInputPhone.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid phone number.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputPhone, R"(^[0-9()\-]{1,15}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    return tmpUserInputPhone;
}


void PhoneExactFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
    for (const auto &rec : records) {
		if (rec.PhoneNum == userInputPhone ) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}	
	std::cout <<"\n" << matchCount << " records found"<<std::endl;	
	if (!found) {
		std::cout << "No record found with phone number: " << userInputPhone << std::endl;
   	}
} 


void PhonePartialFound(const std::vector<Record> &records) {
	bool found = false;
	int matchCount  = 0;
                   
    for (const auto &rec : records) {
    	
		if (rec.PhoneNum.find(userInputPhone) != std::string::npos) {
			if (!found) {
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
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
            found = true;
            }
	}
	std::cout <<"\n" << matchCount << " records found"<<std::endl;	
	if (!found) {
		std::cout << "No record found with phone number: " << userInputPhone << std::endl;
    }
}

void searchPhoneTask(int userinput, const std::vector<Record> &records) {
	switch (userinput) {
		case 1:
			userInputPhone = getUserInputPhone();
			break;
		case 2:
			PhoneExactFound(records);
			break;
		case 3:
			PhonePartialFound(records);
			break;
		case 4:
			break;
		 default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
	}
}


bool checkDataExist(const std::vector<Record>& records, std::string Record::* member ,const std::string tmpInputData) {
	bool exists = false;
	for (const auto &rec : records) {
		if (rec.*member == tmpInputData) {
			exists = true;
			break;
		}
	}
	return exists;
}


std::string getUserInputNameWithConfirmation(const std::vector<Record>& records) {
    std::string tmpUserInputName;
    std::string tmpAns;
    while (true) {
        std::cout << "Please type in employee's name (< 35 chars): ";
        std::getline(std::cin, tmpUserInputName);
        
        if (tmpUserInputName.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid name.\n";
            continue;
        }
        
        // Validate input using the same regex as before.
        else if (!validateRegex(tmpUserInputName, R"(^(?=.{1,35}$)(?=.*\S)[A-Za-z\s'-]+$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if ((checkDataExist(records, &Record::Name ,tmpUserInputName) == true)) {
			do {
            	std::cout << "Error! Name '" << tmpUserInputName << "' already exists in the data. Do you INSIST this is correct? (y/n): ";
            	std::getline(std::cin, tmpAns);
            
            	if (tmpAns.empty()) {
            		std::cout << "Error: Input cannot be empty. Please enter a valid input\n";
                	continue;
            	}
            	if (!validateRegex(tmpAns, "^[ynYN]$")) {
                	std::cout << "INPUT_ERROR\n";
                	continue;
            	}
            	break;  // Input is valid, exit the loop.
        	} while(true);   
        	if (tmpAns == "Y" || tmpAns == "y") {
        		std::cout << "Alright! you insisted storing (duplicate) Name '"<<tmpUserInputName<<"' under this Employee Record in DB ...\n";
        		return tmpUserInputName;
        	}   	
        	else if (tmpAns == "n" || tmpAns == "N") {
        		continue;
        	}
        }
        else {
        	return tmpUserInputName;
        }
    }
}


std::string getUserInputPhoneNumWithConfirmation(const std::vector<Record>& records) {
    std::string tmpUserInputPhoneNum;
    std::string tmpAns;
    while (true) {
        std::cout << "Please type in employee's phone number (< 35 chars): ";
        std::getline(std::cin, tmpUserInputPhoneNum);
        
        if (tmpUserInputPhoneNum.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid phone number.\n";
            continue;
        }
        
        // Validate input using the same regex as before.
        else if (!validateRegex(tmpUserInputPhoneNum, R"(^[0-9()\-]{1,15}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if ((checkDataExist(records, &Record::PhoneNum ,tmpUserInputPhoneNum) == true)) {
			do {
            	std::cout << "Error! Phone Num '" << tmpUserInputPhoneNum << "' already exists in the data. Do you INSIST this is correct? (y/n): ";
            	std::getline(std::cin, tmpAns);
            
            	if (tmpAns.empty()) {
            		std::cout << "Error: Input cannot be empty. Please enter a valid input\n";
                	continue;
            	}
            	if (!validateRegex(tmpAns, "^[ynYN]$")) {
                	std::cout << "INPUT_ERROR\n";
                	continue;
            	}
            	break;  // Input is valid, exit the loop.
        	} while(true);   
        	if (tmpAns == "Y" || tmpAns == "y") {
        		std::cout << "Alright! you insisted storing (duplicate) phone num '"<<tmpUserInputPhoneNum<<"' under this Employee Record in DB ...\n";
        		return tmpUserInputPhoneNum;
        	}   	
        	else if (tmpAns == "n" || tmpAns == "N") {
        		continue;
        	}
        }
        else {
        	return tmpUserInputPhoneNum;
        }
    }
}

void insertNewRecord(std::vector<Record>& records) {
    Record newRecord;
    
    // Determine new index: if records are empty, start at 1; otherwise, use the last record's index + 1.
    newRecord.Idx = records.empty() ? 1 : records.back().Idx + 1;
    std::cout << "\n--- Inserting New Record ---\n";
    
    newRecord.Name = getUserInputNameWithConfirmation(records);
    
	do {
        std::cout << "Please type in employee's ic (< 10 chars) : "; 
        std::getline(std::cin, newRecord.IC); 
		
        if (newRecord.IC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(newRecord.IC,R"(^[A-Za-z0-9]{1,9}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if (checkDataExist(records, &Record::IC ,newRecord.IC) == true) {
        	std::cout << "Error! IC No. '"<<newRecord.IC<<"' already exists in employee records DB, please try again!\n";
        	continue;
        }
		break;
    } while (true); 
  
  
	do {
        std::cout << "Please type in employee's email (< 35 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, newRecord.Email); 
		
        if (newRecord.Email.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid email.\n";
            continue;
        }
        else if (!validateRegex(newRecord.Email, R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
      	else if (checkDataExist(records, &Record::Email, newRecord.Email) == true) {
      		std::cout << "Error! Email '"<<newRecord.Email<<"' already exists in employee records DB, please try again!\n";
      		continue;
      	}
		break;
    } while (true); // Repeat until a valid filename is entered
	std::cout << newRecord.Email<<std::endl;

    newRecord.PhoneNum = getUserInputPhoneNumWithConfirmation(records);
    
    
	do {
        std::cout << "To enter employee's date of birth, please adhere to the format shown in prompt below...\n";
        std::cout << "Enter a data (dd-mm-yyyy) : "; 
        std::getline(std::cin, newRecord.BirthDate); 
		
        if (newRecord.BirthDate.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(newRecord.BirthDate,R"(^(0[1-9]|[12]\d|3[01])-(0[1-9]|1[0-2])-\d{4}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        std::replace(newRecord.BirthDate.begin(), newRecord.BirthDate.end(), '-', '/');
		break;
    } while (true); 
    
    
    do {
        std::cout << "To enter employee's date of hire, please adhere to the format shown in prompt below...\n";
        std::cout << "Enter a data (dd-mm-yyyy) : "; 
        std::getline(std::cin, newRecord.HireDate); 
		
        if (newRecord.HireDate.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(newRecord.HireDate,R"(^(0[1-9]|[12]\d|3[01])-(0[1-9]|1[0-2])-\d{4}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        std::replace(newRecord.HireDate.begin(), newRecord.HireDate.end(), '-', '/');
		break;
    } while (true); 
    
    
    /*
    newRecord.Name = "Melvin";
    newRecord.Email = "melvinlee0199@gmail.com";
    newRecord.IC = "T01765821";
    newRecord.PhoneNum = "(65)-84158771";
    newRecord.HireDate = "01/01/2001";
    newRecord.BirthDate = "02/02/2002";
    */
    records.push_back(newRecord);
    std::cout << "New record inserted successfully!\n";
}

int updateMenu(std::string updateIC, std::string updateName, std::string updatePhoneNum, std::string updateBirthDate, std::string updateHireDate, std::string updateEmail) {
	int updateEnteredNumber;
	std::string tmpUpdateEnteredNumber;
	
	do {
		std::cout << "\n+++ Item to be updated +++"<<std::endl;
		std::cout << "++++++++++++++++++++++++++"<<std::endl;
		std::cout << "1) Update IC			(curr. value = '"<<updateIC<<"')"<<std::endl;
		std::cout << "2) Update Email			(curr. value = '"<<updateEmail<<"')"<<std::endl;
		std::cout << "3) Update Name			(curr. value = '"<<updateName<<"')"<<std::endl;
		std::cout << "4) Update Phone Number		(curr. value = '"<<updatePhoneNum<<"')"<<std::endl;
		std::cout << "5) Update Birth Date		(curr. value = '"<<updateBirthDate<<"')"<<std::endl;
		std::cout << "6) Update Hired Date		(curr. value = '"<<updateHireDate<<"')"<<std::endl;
		std::cout << "7) Done with update"<<std::endl;
		std::cout << "++++++++++++++++++++++++++"<<std::endl;
	   
		std::cout <<"Please enter your choice (1 - 7): "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUpdateEnteredNumber); 
		
       	if (tmpUpdateEnteredNumber.empty()) {
        	std::cout << "Error: Input cannot be empty. Please enter a valid number.\n";
            continue;
       	}
        
       	else if (!validateRegex(tmpUpdateEnteredNumber, R"(^[1-7]$)")) {
        	std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
	}while(true);
	updateEnteredNumber = std::stoi(tmpUpdateEnteredNumber);
	return (updateEnteredNumber);
}

std::string updateEmployeeIC(std::vector<Record>& records, const std::string& currentIC) {
    std::string newIC;
    do {
        std::cout << "Please enter the new IC (< 10 chars): ";
        std::getline(std::cin, newIC);
        
        if (newIC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid IC.\n";
            continue;
        }
        else if (!validateRegex(newIC, R"(^[A-Za-z0-9]{1,9}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if (checkDataExist(records, &Record::IC, newIC)) {
            std::cout << "Error! IC No. '" << newIC << "' already exists in employee records DB, please try again!\n";
            continue;
        }
        break;
    } while (true);
    return newIC;
}


std::string updateEmployeeEmail(std::vector<Record>& records, const std::string& currentEmail) {
    std::string newEmail;
    do {
        std::cout << "Please type in employee's email (< 35 chars): ";
        std::getline(std::cin, newEmail);

        if (newEmail.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid email.\n";
            continue;
        }
        // Using a simple email regex pattern.
        else if (!validateRegex(newEmail, R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if (checkDataExist(records, &Record::Email, newEmail)) {
            std::cout << "Error! Email '" << newEmail << "' already exists in employee records DB, please try again!\n";
            continue;
        }
        break;
    } while (true);
    return newEmail;
}


std::string updateEmployeeName(std::vector<Record>& records, const std::string& currentName) {
    std::string newName;
    std::string tmpAns;
    do {
        std::cout << "Please enter the new employee name (<35 chars): ";
        std::getline(std::cin, newName);
        
        if (newName.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid name.\n";
            continue;
        }
        // Validate that the name contains only letters and spaces and is between 1 and 50 characters long.
        else if (!validateRegex(newName, R"(^(?=.{1,35}$)(?=.*\S)[A-Za-z\s'-]+$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if ((checkDataExist(records, &Record::Name ,newName) == true)) {
			do {
            	std::cout << "Error! Name '" << newName << "' already exists in the data. Do you INSIST this is correct? (y/n): ";
            	std::getline(std::cin, tmpAns);
            
            	if (tmpAns.empty()) {
            		std::cout << "Error: Input cannot be empty. Please enter a valid input\n";
                	continue;
            	}
            	if (!validateRegex(tmpAns, "^[ynYN]$")) {
                	std::cout << "INPUT_ERROR\n";
                	continue;
            	}
            	break;  // Input is valid, exit the loop.
        	} while(true);   
        	if (tmpAns == "Y" || tmpAns == "y") {
        		std::cout << "Alright! you insisted storing (duplicate) Name '"<<newName<<"' under this Employee Record in DB ...\n";
        		return newName;
        	}   	
        	else if (tmpAns == "n" || tmpAns == "N") {
        		continue;
        	}
        }
        break;
    } while (true);
    return newName;
}



std::string updateEmployeePhoneNum(std::vector<Record>& records, const std::string& currentPhoneNum) {
    std::string newPhoneNum;
    std::string tmpAns;
    do {
        std::cout << "Please type in employee's phone number (<15 chars): ";
        std::getline(std::cin, newPhoneNum);

        if (newPhoneNum.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid phone number.\n";
            continue;
        }
        // Validate that the phone number contains only digits and is between 7 and 15 characters long.
        else if (!validateRegex(newPhoneNum, R"(^[0-9()\-]{1,15}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        else if ((checkDataExist(records, &Record::PhoneNum , newPhoneNum) == true)) {
			do {
            	std::cout << "Error! Phone Num '" << newPhoneNum << "' already exists in the data. Do you INSIST this is correct? (y/n): ";
            	std::getline(std::cin, tmpAns);
            
            	if (tmpAns.empty()) {
            		std::cout << "Error: Input cannot be empty. Please enter a valid input\n";
                	continue;
            	}
            	if (!validateRegex(tmpAns, "^[ynYN]$")) {
                	std::cout << "INPUT_ERROR\n";
                	continue;
            	}
            	break;  // Input is valid, exit the loop.
        	} while(true);   
        	if (tmpAns == "Y" || tmpAns == "y") {
        		std::cout << "Alright! you insisted storing (duplicate) phone num '"<< newPhoneNum<<"' under this Employee Record in DB ...\n";
        		return newPhoneNum;
        	}   	
        	else if (tmpAns == "n" || tmpAns == "N") {
        		continue;
        	}
        }
        break;
    } while (true);
    return newPhoneNum;
}


std::string updateEmployeeBirthDate(std::vector<Record>& records, const std::string& currentBirthDate) {
    std::string newBirthDate;
    do {
        std::cout << "Please enter the new birth date (dd-mm-yyyy): ";
        std::getline(std::cin, newBirthDate);
        
        if (newBirthDate.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid birth date.\n";
            continue;
        }
        
        // Check that the input has exactly 10 characters and '-' is used at the correct positions.
        if (newBirthDate.size() != 10 || newBirthDate[2] != '-' || newBirthDate[5] != '-') {
            std::cout << "INPUT_ERROR: Date format must be dd-mm-yyyy with '-' as the delimiter.\n";
            continue;
        }
        
        // Validate the basic date format using regex.
        if (!validateRegex(newBirthDate, R"(^[0-9]{2}-[0-9]{2}-[0-9]{4}$)")) {
            std::cout << "INPUT_ERROR: Date format must be dd-mm-yyyy.\n";
            continue;
        }
        
        // Parse the date components: day, month, and year.
        int day, month, year;
        char dash1, dash2;
        std::istringstream iss(newBirthDate);
        if (!(iss >> day >> dash1 >> month >> dash2 >> year) || dash1 != '-' || dash2 != '-') {
            std::cout << "INPUT_ERROR: Unable to parse date components.\n";
            continue;
        }
        
        // Validate month range.
        if (month < 1 || month > 12) {
            std::cout << "INPUT_ERROR: Month must be between 01 and 12.\n";
            continue;
        }
        
        // Determine the maximum day allowed for the given month (with leap year check for February).
        int maxDay;
        switch (month) {
            case 4: case 6: case 9: case 11:
                maxDay = 30;
                break;
            case 2:
                // Leap year: divisible by 400 or divisible by 4 but not by 100.
                if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
                    maxDay = 29;
                } else {
                    maxDay = 28;
                }
                break;
            default:
                maxDay = 31;
        }
        
        // Validate day range.
        if (day < 1 || day > maxDay) {
            std::cout << "INPUT_ERROR: Day must be between 1 and " << maxDay
                      << " for month " << month << ".\n";
            continue;
        }
        
        // If all validations pass, break out of the loop.
        break;
    } while (true);
    
    // Convert the date format from dd-mm-yyyy to dd/mm/yyyy.
    std::replace(newBirthDate.begin(), newBirthDate.end(), '-', '/');
    return newBirthDate;
}


std::string updateEmployeeHireDate(std::vector<Record>& records, const std::string& currentHireDate) {
    std::string newHireDate;
    do {
        std::cout << "Please enter the new hire date (dd-mm-yyyy): ";
        std::getline(std::cin, newHireDate);
        
        if (newHireDate.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid hire date.\n";
            continue;
        }
        
        // Check that the input has exactly 10 characters and the delimiters are '-' at the correct positions.
        if (newHireDate.size() != 10 || newHireDate[2] != '-' || newHireDate[5] != '-') {
            std::cout << "INPUT_ERROR: Date format must be dd-mm-yyyy with '-' as the delimiter.\n";
            continue;
        }
        
        // Validate the basic date format using regex.
        if (!validateRegex(newHireDate, R"(^[0-9]{2}-[0-9]{2}-[0-9]{4}$)")) {
            std::cout << "INPUT_ERROR: Date format must be dd-mm-yyyy.\n";
            continue;
        }
        
        // Parse the date components: day, month, and year.
        int day, month, year;
        char dash1, dash2;
        std::istringstream iss(newHireDate);
        if (!(iss >> day >> dash1 >> month >> dash2 >> year)) {
            std::cout << "INPUT_ERROR: Unable to parse date components.\n";
            continue;
        }
        
        // Ensure the delimiters are correct.
        if (dash1 != '-' || dash2 != '-') {
            std::cout << "INPUT_ERROR: Date format must use '-' as the delimiter.\n";
            continue;
        }
        
        // Validate month range.
        if (month < 1 || month > 12) {
            std::cout << "INPUT_ERROR: Month must be between 01 and 12.\n";
            continue;
        }
        
        // Determine maximum day for the month (including leap year check for February).
        int maxDay;
        switch (month) {
            case 4: case 6: case 9: case 11:
                maxDay = 30;
                break;
            case 2:
                // Leap year check: divisible by 400 or divisible by 4 but not by 100.
                if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
                    maxDay = 29;
                } else {
                    maxDay = 28;
                }
                break;
            default:
                maxDay = 31;
        }
        
        // Validate day range.
        if (day < 1 || day > maxDay) {
            std::cout << "INPUT_ERROR: Day must be between 1 and " << maxDay 
                      << " for month " << month << ".\n";
            continue;
        }
        
        // All checks passed.
        break;
    } while (true);
    
    // Convert the date format from dd-mm-yyyy to dd/mm/yyyy.
    std::replace(newHireDate.begin(), newHireDate.end(), '-', '/');
    
    return newHireDate;
}


void submitEmployeeRecordUpdate(std::vector<Record>& records, Record& rec) {
    std::cout<<"Done! Going back to main menu ..."<<std::endl;
}


void updataRecord(std::vector<Record>& records) {
	std::string tmpUserInputIC;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout << "Please type in existing employee's IC (< 10 chars) : "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserInputIC); 
		
        if (tmpUserInputIC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid ic.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputIC,R"(^[A-Za-z0-9]{1,9}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
    
	bool found = false;
	int matchCount  = 0;
	int updateOption;
	
    for (auto &rec : records) {
		if (rec.IC == tmpUserInputIC) {
			if (!found) {
                std::cout << "\n======================================================================================================================\n";
                std::cout << std::left 
                          << std::setw(11) << "IC"
                          << std::setw(36) << "Name"
                          << std::setw(16) << "Phone"
                          << std::setw(16) << "Birth Date"
                          << std::setw(16) << "Hired Date"
                          << "Email" 
                          << std::endl;
                std::cout << "======================================================================================================================\n";
            }
            matchCount ++;
            std::cout << std::left
                      << std::setw(11) << rec.IC
                      << std::setw(36) << rec.Name
                      << std::setw(16) << rec.PhoneNum
                      << std::setw(16) << rec.BirthDate
                      << std::setw(16) << rec.HireDate
                      << rec.Email
                      << std::endl;
			std::cout <<"\n" << matchCount << " records found with IC EXACTLY matching '"<<tmpUserInputIC<<"'" <<std::endl;
            found = true;
            do {
            	updateOption = updateMenu(rec.IC, rec.Name, rec.PhoneNum, rec.BirthDate, rec.HireDate, rec.Email);
				std::cout << std::endl;
				switch (updateOption) {
					case 1:
						rec.IC = updateEmployeeIC(records, rec.IC);
						break;
					case 2:
						rec.Email = updateEmployeeEmail(records, rec.Email);
						break;
					case 3:
						rec.Name = updateEmployeeName(records, rec.Name);
						break;
					case 4:
						rec.PhoneNum = updateEmployeePhoneNum(records, rec.PhoneNum);
						break;
					case 5:
				    	rec.BirthDate = updateEmployeeBirthDate(records, rec.BirthDate);
    					break;
					case 6:
						rec.HireDate = updateEmployeeHireDate(records, rec.HireDate);
    					break;
					case 7:
					    submitEmployeeRecordUpdate(records, rec);
    					break;
					default:
						std::cout<< "Invalid Choice => " << updateOption << ", please try again!" << std::endl;;
				}
            }while(updateOption !=7);     	
			}
		}	
	if (!found) {
		std::cout << "Error! IC No. '" << tmpUserInputIC << "' DOES NOT exists in employee records DB!"<< std::endl;
	}
}

void deleteRecord(std::vector<Record>& records) {
    std::string tmpUserInputIC;
    std::string tmpAns;
    bool found = false;
    int matchCount = 0;

    // Ask for a valid IC.
    do {
        std::cout << "Please type in existing employee's IC (< 10 chars): ";
        std::getline(std::cin, tmpUserInputIC);
        
        tmpUserInputIC = trim(tmpUserInputIC);
        
        if (tmpUserInputIC.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid IC.\n";
            continue;
        }
        else if (!validateRegex(tmpUserInputIC, R"(^[A-Za-z0-9]{1,9}$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
        break;
    } while (true);
    
    // Iterate over the records using an iterator to safely erase matching records.
    for (auto it = records.begin(); it != records.end(); ) {
        if (it->IC == tmpUserInputIC) {
            found = true;
            matchCount++;
            
            // Display header once for the first match.
            if (matchCount == 1) {
                std::cout << "\n======================================================================================================================\n";
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
            }
            
            // Display the matching record.
            std::cout << std::left
                      << std::setw(8)  << it->Idx
                      << std::setw(11) << it->IC
                      << std::setw(36) << it->Name
                      << std::setw(16) << it->PhoneNum
                      << std::setw(16) << it->BirthDate
                      << std::setw(16) << it->HireDate
                      << it->Email
                      << std::endl;
            std::cout << "\n" << matchCount 
                      << " record(s) found with IC EXACTLY matching '" 
                      << tmpUserInputIC << "'" << std::endl;
            
            // Confirm deletion.
            do {
                std::cout << "Confirm deletion of the record? (y/n): ";
                std::getline(std::cin, tmpAns);
                
                if (tmpAns.empty()) {
                    std::cout << "Error: Input cannot be empty. Please enter a valid input\n";
                    continue;
                }
                if (!validateRegex(tmpAns, R"(^[yYnN]$)")) {
                    std::cout << "INPUT_ERROR\n";
                    continue;
                }
                break;
            } while (true);
            
            if (tmpAns == "Y" || tmpAns == "y") {
                // Erase the record; erase returns an iterator to the next element.
                it = records.erase(it);
                std::cout << "Record deleted successfully.\n";
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
    
    if (!found) {
        std::cout << "Error! IC No. '" << tmpUserInputIC 
                  << "' DOES NOT exist in the employee records DB!\n";
    }
    
    // Update the Idx for all remaining records so that the array indices are shifted.
    for (size_t i = 0; i < records.size(); i++) {
        records[i].Idx = static_cast<int>(i + 1);
    }
}


void exportRecord(std::vector<Record>& records) {
    std::string fileName;
    int count = 0;
    
    do {
        std::cout << "Enter file name to export data: ";
        std::getline(std::cin, fileName);
        fileName = trim(fileName);
        if (fileName.empty()) {
            std::cout << "Error: File name cannot be empty. Please try again.\n";
        } else {
            break;
        }
    } while (true);
    
    // add".csv" if never input it in
    if (fileName.find('.') == std::string::npos) {
        fileName += ".csv";
    }
    
    if (records.empty()) {
    	std::cout << "No data captured !"<<std::endl;
    	return;
    }
    
    std::ofstream outFile(fileName);
    
    // Write the header row.
    outFile << "Idx,Name,Email,IC,PhoneNum,HireDate,BirthDate\n";
    
    // Write each record as a row in CSV format.
    for (const auto &rec : records) {
        outFile << rec.Idx << ','
        		<< rec.Name << ','
        		<< rec.Email << ','
                << rec.IC << ','
                << rec.PhoneNum << ','
                << rec.HireDate << ','
                << rec.BirthDate << '\n';
		count++;
    }
    
    outFile.close();
    std::cout << "Done! Total no. of records written to output file '" << fileName << "' = " << count <<" records"<<std::endl;
}
