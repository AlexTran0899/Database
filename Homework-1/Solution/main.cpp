#include <iostream>
#include "database.h"
using namespace std;

void printData(string id, string first_name, string last_name, string age, 
			   string ticket_num, string fare, string purchase_date)
{
	cout << "ID: " << id << " first Name: " << first_name << " Last Name: " << last_name
		 << " Age: " << age << " Ticket Num: " << ticket_num << " Fare: " << fare 
		 << " Purchase Date: " << purchase_date << endl;
}

void menu()
{
  
   cout << endl << endl
        << "1) Create new database\n"
        << "2) Open database\n"
        << "3) Close database\n"
        << "4) Read record\n"
        << "5) Display record\n"
        << "6) Update record\n"
        << "7) Create report\n"
        << "8) Add record\n"
        << "9) Delete record\n"
        << "10) Quit\n";
}

int main(int argc, char **argv)
{
	string id, first_name, last_name, age, ticket_num, fare, purchase_date;
	int selection = -1;
    Database db;
    string filename;
    int recordNum;
  
	
	cout << endl << "Welcome to the database part 1" << endl;
		 
    bool Done = false;
	while (!Done) {
        menu();
		cout  << "Please make your selection: ";
        cin >> selection;
        switch (selection) {
            case 1: // Create new database
                cout << "Enter database name: ";
                cin >> filename;
                if(db.createDb(filename)){
                	cout << "Database created." << endl;
                }
                break;
            case 2: // Open database
                cout << "Enter database name to open: ";
                cin >> filename;
                if(db.openDb(filename)) {
                    cout << "Database opened successfully." << endl;
                } else {
                    cout << "Failed to open database." << endl;
                }
                break;
            case 3: // Close database
                db.closeDb();
                break;
            case 4: // Read record
                cout << "Enter record number to display: ";
                cin >> recordNum;
                if(db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(id, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                break;
            case 5: // Display record
                // Implementation depends on how the Dtabase class handles displaying a record given the primary key
            case 6: // Update record
                // Implementation depends on how the Database class handles updates
                break;
            case 7: // Create report
                // Could iterate over all records and display them or write to a file
                break;
            case 8: // Add record
                // Gather input from the user and use writeRecord or another method to add
                break;
            case 9: // Delete record
                // Implementation depends on how the Database class handles deletion
                break;
            case 10: // Quit
                if (!db.isOpen())
                {
                   cout << "Exiting program." << endl;
                   Done = true;
                }
                else
                   cout << "Please close the database before exiting." << endl;
                break;
            default:
                cout << "Invalid selection, please try again." << endl;
                break;
        }
    }

    return 0;
	
}
