//
// Created by Alex Tran on 2/17/24.
//

#ifndef SELF_TRAVELERINFO_H
#define SELF_TRAVELERINFO_H

#include <iostream>

class TravelerInfo {
private:
    int passengerId;
    std::string firstName;
    std::string lastName;
    int age;
    std::string ticketNum;
    double fare;
    std::string dateOfPurchase;
public:
    TravelerInfo();

    TravelerInfo(int passengerId, const std::string &firstName, const std::string &lastName, int age,
                 const std::string &ticketNum, double fare, const std::string &dateOfPurchase);

    ~TravelerInfo();

    void marshal(std::ofstream &out, bool isBlankRecord = false) const;
    void unmarshal(const std::string &line);

    void parseString(const std::string &line);

    void print() const;
};


#endif //SELF_TRAVELERINFO_H
