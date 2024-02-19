//
// Created by Alex Tran on 2/17/24.
//

#include "Concrete/TravelerInfo.hpp"
#include <iomanip>
#include <memory>
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

void TravelerInfo::marshal(std::ostream &out, bool saveBlankRecord) const {
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

unsigned int TravelerInfo::getID() const {
    return passengerId;
};


void TravelerInfo::clear() {
    passengerId = -1;
    firstName = "BLANK";
    lastName = "BLANK";
    age = -1;
    ticketNum = "BLANK";
    fare = -1;
    dateOfPurchase = "BLANK";
}

void TravelerInfo::unmarshal(const std::string &line) {
    if(Utils::isBlankRecord(line)) {
        clear();
        return;
    }
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

void TravelerInfo::getUserInput() {
    std::string temp;

    std::cout << "Enter passenger ID: ";
    std::getline(std::cin, temp);
    passengerId = std::stoi(temp);

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);

    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);

    std::cout << "Enter age: ";
    std::getline(std::cin, temp);
    age = std::stoi(temp);

    std::cout << "Enter ticket number: ";
    std::getline(std::cin, ticketNum);

    std::cout << "Enter fare: ";
    std::getline(std::cin, temp);
    fare = std::stod(temp);

    std::cout << "Enter date of purchase (DD/MM/YYYY): ";
    std::getline(std::cin, dateOfPurchase);
}