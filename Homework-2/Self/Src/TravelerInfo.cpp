//
// Created by Alex Tran on 2/17/24.
//

#include "Concrete/TravelerInfo.hpp"
#include <sstream>
#include <fstream>
#include "../Utils/Utils.h"

TravelerInfo::TravelerInfo() {}

TravelerInfo::TravelerInfo(int passengerId, const std::string &firstName, const std::string &lastName, int age,
                           const std::string &ticketNum, double fare, const std::string &dateOfPurchase)
        : passengerId(passengerId), firstName(firstName), lastName(lastName), age(age),
          ticketNum(ticketNum), fare(fare), dateOfPurchase(dateOfPurchase) {
}

TravelerInfo::~TravelerInfo() {
//    std::cout << "In TravelerInfo Destructor" << std::endl;
}

void TravelerInfo::marshal(std::ofstream &out, bool saveBlankRecord) const {
    if (saveBlankRecord) {
        out << std::left << std::setw(99) << "-1" << std::endl;
        return;
    }

    out << std::setw(9) << std::left << passengerId
        << std::setw(20) << std::left << Utils::replaceSpacesWithUnderScore(firstName)
        << std::setw(20) << std::left << Utils::replaceSpacesWithUnderScore(lastName)
        << std::setw(10) << std::left << age
        << std::setw(20) << std::left << Utils::replaceSpacesWithUnderScore(ticketNum)
        << std::setw(10) << std::fixed << std::setprecision(2) << std::left << fare
        << std::setw(10) << std::left << dateOfPurchase << std::endl;
}

void TravelerInfo::unmarshal(const std::string &line) {
    std::istringstream stream(line);
    std::string temp;

    stream >> temp;
    this->passengerId = stoi(temp);

    stream >> temp;
    firstName = Utils::replaceUnderScoreWithSpaces(temp);

    stream >> temp;
    lastName = Utils::replaceUnderScoreWithSpaces(temp);

    stream >> temp;
    age = std::stoi(temp);

    stream >> temp;
    ticketNum = Utils::replaceUnderScoreWithSpaces(temp);

    stream >> temp;
    fare = std::stod(temp);

    stream >> temp;
    dateOfPurchase = Utils::replaceUnderScoreWithSpaces(temp);
}

void TravelerInfo::parseString(const std::string &line) {
    try {
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
    } catch (std::exception e) {
        std::cerr << "Error parsing passenger info" << std::endl;
    }
}

void TravelerInfo::print() const {
    std::cout << std::setw(10) << std::left << passengerId
              << std::setw(20) << std::left << firstName
              << std::setw(20) << std::left << lastName
              << std::setw(10) << std::left << age
              << std::setw(20) << std::left << ticketNum
              << std::setw(10) << std::fixed << std::setprecision(2) << std::left << fare
              << std::setw(10) << std::left << dateOfPurchase << std::endl;
}

int  TravelerInfo::getRecordSize() const {
    return recordSize;
};