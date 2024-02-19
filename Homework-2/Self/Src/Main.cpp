#include "Concrete/TravelerInfo.hpp"
#include "Factory/DatabaseFactory.hpp"
#include "Database.hpp"
#include <fstream>
#include <iostream>


void travelerInfoTest();

void databaseTest();

void printMenu();

void readRecord(Database &db, std::shared_ptr<IRecord> rec);

void addRecord(Database &db, std::shared_ptr<IRecord> rec);

void createNewDB(Database &db, std::shared_ptr<IRecord> rec);

void openDB(Database &db, std::shared_ptr<IRecord> rec);

void displayRecord(Database &db, std::shared_ptr<IRecord> rec);

void deleteRecord(Database &db, std::shared_ptr<IRecord> rec);

void updateRecord(Database &db, std::shared_ptr<IRecord> rec);


int main() {
    travelerInfoTest();
    databaseTest();
    std::shared_ptr<IRecord> record = DatabaseFactory::CreateTravelerInfo();
    // at some point this will be another menu allowing the user the select which database type.
    Database db(record);
    std::string input = "0";
    std::string filename = "TravelerInfo";

    std::cout << std::endl;
    while (input != "-1") {
        printMenu();
        getline(std::cin, input);
        int command = 0;

        try {
            command = stoi(input);
        } catch (std::exception e) {
            std::cout << "invalid command!" << std::endl;
        }

        switch (command) {
            case 0:
                createNewDB(db,record);
                break;
            case 1:
                openDB(db,record);
                break;
            case 2:
                db.close();
                break;
            case 3:
                displayRecord(db,record);
                break;
            case 4:
                updateRecord(db, record);
                break;
            case 5:
                db.createReport(record);
                break;
            case 6:
                addRecord(db,record);
                break;
            case 7:
                deleteRecord(db,record);
                break;
            case 8:
                readRecord(db,record);
                break;
            case -1:
                db.close();
                std::cout << "have a good day, and a good life, goodbye :)" << std::endl;
                break;
            default:
                std::cout << "unknown command " << std::endl;
        }
    }

    return 0;
}

void updateRecord(Database &db, std::shared_ptr<IRecord> rec) {
    TravelerInfo t;
    t.getUserInput();
    db.updateRecord(t);
}

void addRecord(Database &db, std::shared_ptr<IRecord> rec) {
    TravelerInfo t;
    t.getUserInput();
    db.addRecord(t);
}

void readRecord(Database &db, std::shared_ptr<IRecord> rec){
    std::cout << "Please enter a record number: " << std::endl;
    std::string input;
    getline(std::cin, input);
    db.readRecord(stoi(input), rec);
    rec->print();
}

void createNewDB(Database &db, std::shared_ptr<IRecord> rec) {
    std::string filename = "TravelerInfo";
    // std::getline(std::cin, filename);
    if (db.create(filename)) {
        std::cout << filename << " Database Created" << std::endl;
    }
}

void openDB(Database &db, std::shared_ptr<IRecord> rec){
    std::string filename = "TravelerInfo";
    // std::getline(std::cin, filename);
    if (db.open(filename)) {
        std::cout << filename << " Database Opened" << std::endl;
    }
}

void displayRecord(Database &db, std::shared_ptr<IRecord> rec){
    std::string id;
    std::cout << "Display - Please enter an id number: " << std::endl;
    std::getline(std::cin, id);
    db.displayRecord(stoi(id), rec);
}

void deleteRecord(Database &db, std::shared_ptr<IRecord> rec) {
    std::string id;
    std::cout << "Delete - Please enter an id number: " << std::endl;
    std::getline(std::cin, id);
    db.deleteRecord(stoi(id),rec);
}

void printMenu() {
    std::cout << "----- USER OPTIONS -----" << std::endl;
    std::cout << "0: Create new database" << std::endl;
    std::cout << "1: Open database" << std::endl;
    std::cout << "2: Close database" << std::endl;
    std::cout << "3: Display record" << std::endl;
    std::cout << "4: Update record" << std::endl;
    std::cout << "5: Create report" << std::endl;
    std::cout << "6: Add record" << std::endl;
    std::cout << "7: Delete record" << std::endl;
    std::cout << "8: Read record" << std::endl;
    std::cout << "-1: Quit program" << std::endl;
    std::cout << "Please enter a number: " << std::endl;
}

void databaseTest() {
    try{
        std::shared_ptr<IRecord> record = DatabaseFactory::CreateTravelerInfo();
        Database db(record);
        std::string filename = "TravelerInfoTest";
        db.create(filename);
        db.open(filename);

        TravelerInfo p(13, "John", "Doe", 30, "TICKET12345", 299.99, "2023-02-18");
        db.addRecord(p);
        db.displayRecord(13, record);
        if(record->getID() == p.getID()) {
            std::cout << "Create Record - success" << std::endl;
        } else {
            std::cerr << "Create Record - failed" << std::endl;
        }

        TravelerInfo p2(13,"NotJohn","Doe",30,"TICKET12345",299.99,"2023-02-18");
        db.updateRecord(p2);
        db.displayRecord(13, record);
        if(record->getID() == p2.getID()) {
            std::cout << "Update Record - success" << std::endl;
        } else {
            std::cerr << "Update Record - failed" << std::endl;
        }

        db.deleteRecord(13,record);
        unsigned int temp = 0;
        if(!db.binarySearch(13, temp, record)) {
            std::cout << "Delete Record - success" << std::endl;
        } else {
            std::cerr << "Delete Record - failed" << std::endl;
        }

        db.close();
        if(!db.isOpen()) {
            std::cout << "Close DB - success" << std::endl;
        } else {
            std::cerr << "Close DB - failed" << std::endl;
        }

    } catch (std::exception e) {
        std::cerr << "Database implementation is faulty" << std::endl;
    }
}


void travelerInfoTest() {
    std::cout << "** Begin of TravelerInfo Test **" << std::endl;
    std::ifstream Din("../TestData/TravelerInfoTest.csv");
    std::ofstream Dout;

    if (!Din) {
        std::cerr << "Failed to Open File." << std::endl;
    }
    std::string line;
    TravelerInfo t;

    try {
        std::getline(Din, line);
        t.parseString(line);
        std::cout << "Read data from CSV text file is correct" << std::endl;
    } catch (std::exception e) {
        std::cout << "Read data from CSV text file failed" << std::endl;
    }

    Dout.open("../TestData/TravelerInfoTest.data");

    try {
        t.marshal(Dout);
        t.marshal(Dout, true);
        std::cout << "Write record and blank record to f_db text file is correct" << std::endl;
    } catch (std::exception e) {
        std::cout << "Write record and blank record to f_db text file failed" << std::endl;
    }

    std::ifstream DB("../TestData/TravelerInfoTest.data");
    try {
        std::string line2;
        std::getline(DB, line2);
        TravelerInfo p;
        p.unmarshal(line2);
        std::cout << "Read data from f_db text file is correct" << std::endl;
    } catch (std::exception e) {
        std::cout << "Read data from f_db text file failed" << std::endl;
    }

    DB.close();
    Din.close();
    Dout.close();

    std::cout << "** End of TravelerInfo Test **" << std::endl;
}
