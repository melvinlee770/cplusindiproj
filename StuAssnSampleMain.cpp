#include <iostream>
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

std::string filename;  // sample-50-recs.csv
int datanum;

using namespace std;

int main() 
{
    printWelcomeMsg();

    int userEnteredNumber;

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
                getUserInputQ2(filename, datanum);
                readCSV(filename, datanum);
                break;

            case 3:
                cout << "Design your own function(s) to handle: Display All Records!" << endl;
                break;

            case 4:
                cout << "Design your own function(s) to handle: Search for records by IC!" << endl;
                break;

            case 5:
                cout << "Design your own function(s) to handle: Search for records by Name!" << endl;
                break;

            case 6:
                cout << "Design your own function(s) to handle: Search for records by Email!" << endl;
                break;

            case 7:
                cout << "Design your own function(s) to handle: Search for records by Phone Number!" << endl;
                break;

            case 8:
                cout << "Design your own function(s) to handle: INSERT New Employee Record" << endl;
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
    cout << "Please enter your choice (1 - 12): ";
    cin >> userEnteredNumber;

    return (userEnteredNumber);
}

int queryCurrentNoOfEmpRecs () 
{
  return (empDBSize);

}   // end queryCurrentNoOfEmpRecs () ...


