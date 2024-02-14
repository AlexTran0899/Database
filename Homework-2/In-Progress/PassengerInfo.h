//
// Created by Alex Tran on 1/27/24.
//

#ifndef CPP_PASSENGERINFO_H
#define CPP_PASSENGERINFO_H
#include <iostream>

using namespace std;
class PassengerInfo {
private:
    int PASSENGER_ID;
    string FIRST_NAME;
    string LAST_NAME;
    int AGE;
    string TICKET_NUM;
    double FARE;
    string DATE_OF_PURCHASE;

public:
    PassengerInfo(const int passengerId, const string &firstName, const string &lastName, int age,
                  string ticketNum, const double fare, const string &dateOfPurchase);
    PassengerInfo();

    int getPassengerId();
    string getPassengerInfo();


    string replaceSpacesWithUnderScore(string s);
    string replaceUnderScoreWithSpaces(string s);

    void marshal(stringstream &ss);
    void unmarshal(fstream &Dout);
    void saveBlankRecord(fstream &Dout);
    static PassengerInfo parseData(string line);
    void print();
};


#endif //CPP_PASSENGERINFO_H
