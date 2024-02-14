#include "DB.h"
#include <iomanip>

using namespace std;

void test(string filename);

void printMenu() {
    cout << "----- USER OPTIONS -----" << endl;
    cout << "1: Create new database" << endl;
    cout << "2: Close database" << endl;
    cout << "3: Display record" << endl;
    cout << "4: Update record" << endl;
    cout << "5: Create report" << endl;
    cout << "6: Add record" << endl;
    cout << "7: Delete record" << endl;
    cout << "-1: Quit program" << endl;
    cout << "Please enter a number: " << endl;
}

int main(int argc, char const *argv[]) {
    DB db;
    string input = "0";
    string filename = "input";

    while (input != "-1") {
        printMenu();
        getline(cin, input);
        int command = 0;
        try {
            command = stoi(input);
        } catch (exception e) {
            cout << "invalid command!" << endl;
        }

        string status = "";
        switch (command) {
            case 1:
                db.createDB(filename);
                break;
            case 2:
                db.close();
                break;
            case 3:
                db.displayRecord(status);
                cout << status << endl;
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case -1:
                db.close();
                cout << "have a good day, and a good life, goodbye :)" << endl;
                break;
            default:
                if (command != 0) {
                    cout << "unknown command " << endl;
                }
        }
    }
    test(filename);
    return 0;
}


void test(string filename) {
    DB db;
    db.createDB(filename);
    cout << "\n------------- Testing readRecord ------------\n";

    // Reads record 0
    // Then prints the values of the 5 fields to the screen with the name of the
    // field and the values read from the record, i.e.,
    // id: 00003 experience: 3 married: no wages: 1.344461678 industry:
    // Business_and_Repair_Service
    int recordNum = 0;
    string status;
    PassengerInfo p;

    if (db.readRecord(status, recordNum, p)) {
        p.print();
    } else {
        cout << status << endl;
    }

    recordNum = 19;
    if (db.readRecord(status, recordNum, p)) {
        p.print();
    } else {
        cout << status << endl;
    }

    recordNum = 6;
    if (db.readRecord(status, recordNum, p)) {
        p.print();
    } else {
        cout << status << endl;
    }

    recordNum = -1;
    if (db.readRecord(status, recordNum, p)) {
        p.print();
    } else {
        cout << status << endl;
    }

    recordNum = 1000;
    if (db.readRecord(status, recordNum, p)) {
        p.print();
    } else {
        cout << status << endl;
    }

    cout << "\n------------- Testing binarySearch ------------\n";

//     Find record with id 42 (should not be found)
    int Id = 10;
    cout << "Looking for Id: " << Id << endl;
    bool found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "passenger ID: " << Id << " not found.\n\n";

// Find record with id 00000 (the first one in the file)
    Id = 2;
    cout << "Looking for Id: " << Id << endl;
    // update the value of recordnum if found, populate the fields
    found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "passenger ID: " << Id << " not found.\n\n";


    // Find record with id 00015 (the last one in the file)
    Id = 15;
    cout << "Looking for Id: " << Id << endl;
    // update the value of recordnum if found, populate the fields
    found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "passenger ID: " << Id << " not found.\n\n";

    Id = 6;
    cout << "Looking for Id: " << Id << endl;
    // update the value of recordnum if found, populate the fields
    found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "passenger ID: " << Id << " not found.\n\n";

    Id = 16;
    cout << "Looking for Id: " << Id << endl;
    // update the value of recordnum if found, populate the fields
    found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "passenger ID: " << Id << " not found.\n\n";

    // Close database
    db.close();

}

