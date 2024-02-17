//
// Created by Alex Tran on 2/17/24.
//

#include "../Include/TravelerInfo.h"
#include <sstream>

TravelerInfo::TravelerInfo() {

}

TravelerInfo::TravelerInfo(int passengerId, const std::string &firstName, const std::string &lastName, int age,
                           const std::string &ticketNum, double fare, const std::string &dateOfPurchase)
        : passengerId(passengerId), firstName(firstName), lastName(lastName), age(age),
          ticketNum(ticketNum), fare(fare), dateOfPurchase(dateOfPurchase) {
}

TravelerInfo::~TravelerInfo(){
    std::cout << "calling the TravelerInfo destructor" << std::endl;
}

void TravelerInfo::marshal(std::ofstream &out, bool isBlankRecord) const {

}

void TravelerInfo::parseString(const std::string &line) {
    try{
        std::istringstream stream(line);

        std::string passengerId;
        getline(stream, passengerId, ',');
        this->passengerId = stoi(passengerId);

        getline(stream, this->firstName, ',');
        getline(stream, this->lastName, ',');

        std::string age;
        getline(stream, age, ',');
        this->age = stoi(age);

        getline(stream, this->ticketNum, ',');

        std::string fare;
        getline(stream, fare, ',');
        this->fare = stod(fare);

        getline(stream, this->dateOfPurchase, ',');
    } catch(std::exception e) {
        std::cerr << "Error parsing passenger info" << std::endl;
    }
}


void TravelerInfo::print() const {

}