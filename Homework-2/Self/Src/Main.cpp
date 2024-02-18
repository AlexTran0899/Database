#include "Concrete/TravelerInfo.hpp"
#include "Database.hpp"
#include <fstream>
#include <iostream>

void travelerInfoTest();
void printMenu();

int main() {
    Database db;
    std::string input = "0";
    std::string filename = "TravelerInfo";

    std::cout << std::endl;
    while(input != "-1") {
        printMenu();
        getline(std::cin, input);
        int command = 0;


        try{
            command = stoi(input);
        } catch(std::exception e) {
            std::cout << "invalid command!" << std::endl;
        }

        TravelerInfo t;
        switch(command) {
            case 0:
                if(db.create(filename, t)){
                    std::cout << filename << " Database Created" << std::endl;
                }
                break;
            case 1:
                std::cout << "Please type in a file name: " << std::endl;
                std::getline(std::cin, filename);
                if(db.open(filename)) {
                    std::cout << filename << " Database Opened" << std::endl;
                }
                break;
            case 2:
                db.close();
                break;
            case 3:
                db.displayRecord(t);
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
                std::cout << "have a good day, and a good life, goodbye :)" << std::endl;
                break;
            default:
                if(command != 0) {
                    std::cout << "unknown command " << std::endl;
                }
        }
    }

    return 0;
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
    std::cout << "-1: Quit program" << std::endl;
    std::cout << "Please enter a number: " << std::endl;
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

    try{
        std::getline(Din, line);
        t.parseString(line);
        std::cout << "Read data from CSV text file is correct" << std::endl;
    } catch(std::exception e) {
        std::cout << "Read data from CSV text file failed" << std::endl;
    }

    Dout.open("../TestData/TravelerInfoTest.data");

    try{
        t.marshal(Dout);
        t.marshal(Dout, true);
        std::cout << "Write record and blank record to f_db text file is correct" << std::endl;
    } catch(std::exception e) {
        std::cout << "Write record and blank record to f_db text file failed" << std::endl;
    }

    std::ifstream DB("../TestData/TravelerInfoTest.data");
    try {
        std::string line2;
        std::getline(DB, line2);
        TravelerInfo p;
        p.unmarshal(line2);
        std::cout << "Read data from f_db text file is correct" << std::endl;
    } catch(std::exception e) {
        std::cout << "Read data from f_db text file failed" << std::endl;
    }

    DB.close();
    Din.close();
    Dout.close();

    std::cout << "** End of TravelerInfo Test **" << std::endl;
}
