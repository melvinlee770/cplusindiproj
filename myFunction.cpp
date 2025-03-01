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
    
    if (captureCount > 1) {
    	std::cerr << "You already captured the file" <<std::endl;
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
        captureCount++;
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
        else if (!validateRegex(tmpUserInputEmail, R"(^(?=.{1,35}$)\S+$)")) {
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
        else if (!validateRegex(newRecord.Email, R"(^(?=.{1,35}$)\S+$)")) {
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

