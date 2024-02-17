#include "TravelerInfo.h"
#include <fstream>
#include <iostream>

void travelerInfoTest();

int main() {




    travelerInfoTest();
    return 0;
}


















void travelerInfoTest() {
    std::cout << "** Begin of TravelerInfo Test **" << std::endl;

    std::ifstream Din("../TestData/TravelerInfoTest.csv");
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

    try{
        std::ofstream Dout("../Data/TravelerInfoTest.data");
        t.marshal(Dout);
        t.marshal(Dout, true);
        std::cout << "Write record and blank record to DB text file is correct" << std::endl;
    } catch(std::exception e) {
        std::cout << "Write record and blank record to DB text file failed" << std::endl;
    }

    try {
        std::ifstream DB("../Data/TravelerInfoTest.data");
        std::string line2;
        std::getline(DB, line2);
        TravelerInfo p;
        p.unmarshal(line2);
        std::cout << "Read data from DB text file is correct" << std::endl;
    } catch(std::exception e) {
        std::cout << "Read data from DB text file failed" << std::endl;
    }

    std::cout << "** End of TravelerInfo Test **" << std::endl;
}
