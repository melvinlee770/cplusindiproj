#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include "Employee.h"
#include "myFunction.h"

// Global variables

#define MAX_NO_OF_RECORDS 300

Employee EmployeeRecordsDB [MAX_NO_OF_RECORDS];

/* Keeps track of the actual number of records
   empDBSize's value MUST BE UPDATED WHENEVER an employee record is : 
   - inserted into EmployeeRecordsDB  OR 
   - deleted from EmployeeRecordsDB
*/
int empDBSize = 0; 

// Function prototypes
void printWelcomeMsg();
int printMainMenuOptions();
int queryCurrentNoOfEmpRecs();
int pirntSearchICMenu();
int printSearchNameMenu();
int printSearchEmailMenu();
int printSearchPhoneMenu();

int userEnteredNumber;
int userEnteredICTask;
int userEneteredNameTask;
int userEnteredEmailTask;
int userEnteredPhoneTask;

std::string filename;
int datanum;

using namespace std;

int main() 
{
    printWelcomeMsg();
    //std::vector<std::unordered_map<std::string, std::string>> data;
    std::vector<Record> records;

    do 
    {
        userEnteredNumber = printMainMenuOptions();
        cout << endl;

        switch (userEnteredNumber) {
            case 1:
                cout << endl;
                cout << "Current no. of Employee Records in Database : " << queryCurrentNoOfEmpRecs() << endl;
                cout << endl;
                break;

            case 2:
                //printHelloWorld();
                //filename = getUserInputQ1();
                //datanum = std::stoi(getUserInputQ2());
                //empDBSize = datanum;
                //loadCSV(filename, records, datanum); //"sample-50-recs.csv"
                loadCSV("sample-50-recs.csv", records, 20); //"sample-50-recs.csv"
                break;

            case 3:
                displayRecords(records);
                break;

            case 4:
            	do {
            		userEnteredICTask = pirntSearchICMenu();
                	searchICTask(userEnteredICTask, records);
            	}while (userEnteredICTask != 4);
            	break;

            case 5:
            	do {
            		userEneteredNameTask = printSearchNameMenu();
            		searchNameTask(userEneteredNameTask , records);
            	}while (userEneteredNameTask != 4);
            	break;

            case 6:
            	do {
            		userEnteredEmailTask = printSearchEmailMenu();
            		searchEmailTask(userEnteredEmailTask , records);
            	}while (userEnteredEmailTask != 4);
                break;

            case 7:
                do {
            		userEnteredPhoneTask = printSearchPhoneMenu();
            		searchPhoneTask(userEnteredPhoneTask, records);
            	}while (userEnteredPhoneTask != 4);
                break;

            case 8:
                	insertNewRecord(records);
                break;

            case 9:
                cout << "Design your own function(s) to handle: Search (by ic) & UPDATE Existing Employee Record" << endl;
                break;

            case 10:
                cout << "Design your own function(s) to handle: Search (by ic) & DELETE Existing Employee Record" << endl;
                break;

            case 11:
                cout << "Design your own function(s) to handle: Write Data From Employee DB To File" << endl;
                break;

            case 12:
                break;

            default:
                cout << endl << "Invalid Choice => " << userEnteredNumber << ", please try again!" << endl;        }

        cout << endl;

    } while (userEnteredNumber != 12);

    cout << "\nThank you for using this program, have a nice day!" << endl;

    return 0;
}

// Function to print the welcome message
void printWelcomeMsg() {
    cout << "\n------------------------------------------------------" << endl;
    cout << "- Welcome to Mr Tian's Assn p2 Sample (Ref) Program! -" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "- Student Number: <2400823>"<<endl;
    cout << "- Student Name: <Lee Yong Zun>"<<endl;
}

// Function to print the main menu and get user input
int printMainMenuOptions() {
    cout << "\n-----------------------------------------------------" << endl;
    cout << "\n 1) Get current no. of records in Employee Database" << endl;
    cout << " 2) Read Data From File and Populate Employee DB" << endl;
    cout << " 3) Display All Records" << endl;
    cout << " 4) Search for records by IC" << endl;
    cout << " 5) Search for records by Name" << endl;
    cout << " 6) Search for records by Email" << endl;
    cout << " 7) Search for records by Phone Number" << endl;
    cout << " 8) INSERT New Employee Record" << endl;
    cout << " 9) Search (by ic) & UPDATE Existing Employee Record" << endl;
    cout << "10) Search (by ic) & DELETE Existing Employee Record" << endl;
    cout << "11) Write Data From Employee DB To File" << endl;
    cout << "12) Quit" << endl;
    cout << "\n-----------------------------------------------------" << endl;
    cout << endl;

    int userEnteredNumber;
	std::string tmpUserEnteredNumber;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
        std::cout <<"Please enter your choice (1 - 12): "; // testing asnwer: sample-50-recs.csv
        std::getline(std::cin, tmpUserEnteredNumber); 
		
        if (tmpUserEnteredNumber.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid number.\n";
            continue;
        }
        
       else if (!validateRegex(tmpUserEnteredNumber, R"(^[1-9]|1[0-2]$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); // Repeat until a valid filename is entered
	userEnteredNumber = std::stoi(tmpUserEnteredNumber);

    return (userEnteredNumber);
    

}

int queryCurrentNoOfEmpRecs () 
{
  return (empDBSize);
}   // end queryCurrentNoOfEmpRecs () ...


int pirntSearchICMenu() {
	std::string tmpUserEnteredNumberICMenu;
	int UserEnteredNumberICMenu;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "\n-----------------------------------------------------" << endl;
        std::cout << "\n1) Enter an ic					(current value = '"<< userInputIC<<"')"<<std::endl;
        std::cout << "2) Search for employee IC = '"<<userInputIC<<"' 		(i.e. EXACT MATCH) "<<std::endl; 
        std::cout << "3) Search for employee IC containing = '"<<userInputIC<<"'	(i.e. PARTIAL MATCH) "<<std::endl; 
        std::cout << "4) Back to main menu ..."<<std::endl;
        cout << "\n-----------------------------------------------------" << endl;

		std::cout <<"Please enter your choice (1-4): ";
        std::getline(std::cin, tmpUserEnteredNumberICMenu); 
		
        if (tmpUserEnteredNumberICMenu.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid choice.\n";
            continue;
        }
        else if (!validateRegex(tmpUserEnteredNumberICMenu, R"(^[1-4]$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
    } while (true); 
    UserEnteredNumberICMenu = std::stoi(tmpUserEnteredNumberICMenu);
    return UserEnteredNumberICMenu;
}


int printSearchNameMenu() {
	std::string tmpUserEnteredNumberNameMenu;
	int UserEnteredNumberNameMenu;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "\n-----------------------------------------------------" << endl;
        std::cout << "\n1) Enter a name						(current value = '"<< userInputName<<"')"<<std::endl;
        std::cout << "2) Search for employee name = '"<<userInputName<<"' 		(i.e. EXACT MATCH) "<<std::endl; 
        std::cout << "3) Search for employee name containing = '"<<userInputName<<"'	(i.e. PARTIAL MATCH) "<<std::endl; 
        std::cout << "4) Back to main menu ..."<<std::endl;
        cout << "\n-----------------------------------------------------" << endl;

		std::cout <<"Please enter your choice (1-4): ";
        std::getline(std::cin, tmpUserEnteredNumberNameMenu); 
		
        if (tmpUserEnteredNumberNameMenu.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid choice.\n";
            continue;
        }
        else if (!validateRegex(tmpUserEnteredNumberNameMenu, R"(^[1-4]$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
		
    } while (true); 
    UserEnteredNumberNameMenu = std::stoi(tmpUserEnteredNumberNameMenu);
    return UserEnteredNumberNameMenu;
}


int printSearchEmailMenu() {
	std::string tmpUserEnteredNumberEmailMenu;
	int UserEnteredNumberEmailMenu;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "\n-----------------------------------------------------" << endl;
        std::cout << "\n1) Enter a email						(current value = '"<< userInputEmail<<"')"<<std::endl;
        std::cout << "2) Search for employee email = '"<<userInputEmail<<"' 			(i.e. EXACT MATCH) "<<std::endl; 
        std::cout << "3) Search for employee email containing = '"<<userInputEmail<<"'	(i.e. PARTIAL MATCH) "<<std::endl; 
        std::cout << "4) Back to main menu ..."<<std::endl;
        cout << "\n-----------------------------------------------------" << endl;

		std::cout <<"Please enter your choice (1-4): ";
        std::getline(std::cin, tmpUserEnteredNumberEmailMenu); 
		
        if (tmpUserEnteredNumberEmailMenu.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid choice\n";
            continue;
        }
        else if (!validateRegex(tmpUserEnteredNumberEmailMenu, R"(^[1-4]$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
		
    } while (true); 
    UserEnteredNumberEmailMenu = std::stoi(tmpUserEnteredNumberEmailMenu);
    return UserEnteredNumberEmailMenu;
}


int printSearchPhoneMenu() {
	std::string tmpUserEnteredNumberPhoneMenu;
	int UserEnteredNumberPhoneMenu;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "\n-----------------------------------------------------" << endl;
        std::cout << "\n1) Enter a phone number						(current value = '"<< userInputPhone<<"')"<<std::endl;
        std::cout << "2) Search for employee phone number = '"<<userInputPhone<<"' 			(i.e. EXACT MATCH) "<<std::endl; 
        std::cout << "3) Search for employee phone number containing = '"<<userInputPhone<<"'	(i.e. PARTIAL MATCH) "<<std::endl; 
        std::cout << "4) Back to main menu ..."<<std::endl;
        cout << "\n-----------------------------------------------------" << endl;

		std::cout <<"Please enter your choice (1-4): ";
        std::getline(std::cin, tmpUserEnteredNumberPhoneMenu); 
		
        if (tmpUserEnteredNumberPhoneMenu.empty()) {
            std::cout << "Error: Input cannot be empty. Please enter a valid choice.\n";
            continue;
        }
        else if (!validateRegex(tmpUserEnteredNumberPhoneMenu, R"(^[1-4]$)")) {
            std::cout << "INPUT_ERROR\n";
            continue;
        }
		break;
		
    } while (true); 
    UserEnteredNumberPhoneMenu = std::stoi(tmpUserEnteredNumberPhoneMenu);
    return UserEnteredNumberPhoneMenu;
}
