//
// Created by Alex Tran on 1/27/24.
//

#include "PassengerInfo.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>

PassengerInfo::PassengerInfo(const int passengerId,
                             const string &firstName,
                             const string &lastName,
                             int age,
                             string ticketNum,
                             const double fare,
                             const string &dateOfPurchase):
                             PASSENGER_ID(passengerId),
                             FIRST_NAME(firstName),
                             LAST_NAME(lastName),
                             AGE(age),
                             TICKET_NUM(ticketNum),
                             FARE(fare),
                             DATE_OF_PURCHASE(dateOfPurchase) {}



PassengerInfo::PassengerInfo() {
    PASSENGER_ID = 0;
    FIRST_NAME = "";
    LAST_NAME = "";
    AGE = 0;
    TICKET_NUM = "";
    FARE = 0;
    DATE_OF_PURCHASE = "";
}

// data into memory
void PassengerInfo::marshal(stringstream &ss){
    string passengerId;
    string firstName;
    string lastName;
    string age;
    string ticketNum;
    string fare;
    string dateOfPurchase;

    ss >> passengerId;
    ss >> firstName;
    ss >> lastName;
    ss >> age;
    ss >> ticketNum;
    ss >> fare;
    ss >> dateOfPurchase;

    PASSENGER_ID = stoi(passengerId);
    FIRST_NAME = replaceUnderScoreWithSpaces(firstName);
    LAST_NAME = replaceUnderScoreWithSpaces(lastName);
    AGE = stoi(age);
    TICKET_NUM = replaceUnderScoreWithSpaces(ticketNum);
    FARE = stod(fare);
    DATE_OF_PURCHASE = replaceSpacesWithUnderScore(dateOfPurchase);
};

int PassengerInfo::getPassengerId(){
    return PassengerInfo::PASSENGER_ID;
};

string PassengerInfo::replaceUnderScoreWithSpaces(string s) {
    for(unsigned i = 0; i < s.length(); i++){
        if(s[i] == '_') {s[i] = ' ';}
        // string in c++ are mutable so this is optimal.
    }
    return s;
}

string PassengerInfo::replaceSpacesWithUnderScore(string s){
    for(unsigned i = 0; i < s.length(); i++){
        if(s[i] == ' ') {s[i] = '_';}
        // string in c++ are mutable so this is optimal.
    }
    return s;
}

// memory to data
void PassengerInfo::unmarshal(ofstream &Dout) {
    Dout << setw(9) << left << PASSENGER_ID
         << setw(20) << left << replaceSpacesWithUnderScore(FIRST_NAME)
         << setw(20) << left << replaceSpacesWithUnderScore(LAST_NAME)
         << setw(10) << left << AGE
         << setw(20) << left << replaceSpacesWithUnderScore(TICKET_NUM)
         << setw(10) << fixed << setprecision(2) << left << FARE
         << setw(10) << left << DATE_OF_PURCHASE << endl;
};

void PassengerInfo::saveBlankRecord(ofstream &Dout) {
    Dout << setw(99) << -1 << endl;
};

void PassengerInfo::print(){
    cout << setw(10) << left << PASSENGER_ID
         << setw(20) << left << FIRST_NAME
         << setw(20) << left << LAST_NAME
         << setw(10) << left << AGE
         << setw(20) << left << TICKET_NUM
         << setw(10) << fixed << setprecision(2) << left << FARE
         << setw(10) << left << DATE_OF_PURCHASE << endl;
}

PassengerInfo PassengerInfo::parseData(string line) {
    int l = 0;
    int length = line.length();
    string data[7];
    int counter = 0;

    for(int r = 0; r < length; r++) {
        if(line[r] == ',') {
            data[counter] = line.substr(l, r - l);
            l = r + 1;
            counter++;
        }
    }
    data[counter] = line.substr(l);
    PassengerInfo passenger(stoi(data[0]),
                            data[1],
                            data[2],
                            stoi(data[3]),
                            data[4],
                            stod(data[5]),
                            data[6]);

    return passenger;
}


