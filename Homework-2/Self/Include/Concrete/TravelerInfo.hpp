//
// Created by Alex Tran on 2/17/24.
//

#ifndef SELF_TRAVELERINFO_HPP
#define SELF_TRAVELERINFO_HPP

#include <iostream>
#include "../Interface/IRecord.hpp"

class TravelerInfo: public IRecord {
private:
    int passengerId;
    std::string firstName;
    std::string lastName;
    int age;
    std::string ticketNum;
    double fare;
    std::string dateOfPurchase;
    int recordSize = 100;
public:
    TravelerInfo();

    TravelerInfo(int passengerId, const std::string &firstName, const std::string &lastName, int age,
                 const std::string &ticketNum, double fare, const std::string &dateOfPurchase);

    ~TravelerInfo();

    unsigned int getID() const;
    void clear();
    void marshal(std::ostream &out, bool saveBlankRecord = false) const;
    void unmarshal(const std::string &line);
    void parseString(const std::string &line);
    void print() const;
    int getRecordSize() const;
    void getUserInput();
};

#include "../../Src/TravelerInfo.cpp"

#endif //SELF_TRAVELERINFO_HPP
