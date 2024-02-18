//
// Created by Alex Tran on 2/17/24.
//

#include "Database.hpp"
#include <iostream>
#include <fstream>


Database::Database() {
    recordCount = 0;
    totalEntries = 0;
    recordSize = 0;
}


bool Database::open(std::string &filename) {
    if (f_db.is_open()) {
        std::cerr << "Another database is currently opened, please close that first" << std::endl;
        return false;
    }

    std::ifstream f_config("../Data/" + filename + ".config");
    this->f_db.open("../Data/" + filename + ".data", std::ios::out | std::ios::in);

    if (!f_config) {
        std::cerr << "Failed to open ../Data/" + filename + ".config" << std::endl;
        return false;
    }

    if (!f_db) {
        std::cerr << "Failed to open ../Data/" + filename + ".data" << std::endl;
        return false;
    }

    std::string temp;
    f_config >> temp;
    this->recordCount = stoi(temp);
    f_config >> temp;
    totalEntries = stoi(temp);
    f_config >> temp;
    recordSize = stoi(temp);
    return true;
}



bool Database::isOpen() {
    return f_db.is_open();
}


Database::~Database() {}


bool Database::create(std::string &filename,IRecord &r) {
    std::ifstream f_csv("../Data/" + filename + ".csv");
    std::ofstream f_db("../Data/" + filename + ".data");
    std::ofstream f_config("../Data/" + filename + ".config");

    if (!f_csv) {
        std::cerr << "Failed to open ../Data/" + filename + ".csv" << std::endl;
        return false;
    }

    if (!f_db) {
        std::cerr << "Failed to open ../Data/" + filename + ".data" << std::endl;
        return false;
    }

    if (!f_config) {
        std::cerr << "Failed to open ../Data/" + filename + ".config" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(f_csv, line)) {
        r.parseString(line);
        r.marshal(f_db);
        r.marshal(f_db, true);
        recordCount += 1;
    }
    totalEntries += recordCount * 2;

    f_config << recordCount << std::setw(20) << totalEntries << std::setw(20) << r.getRecordSize() << std::endl;

    f_csv.close();
    f_db.close();
    f_config.close();
    return true;
};

bool Database::readRecord(unsigned int recordNum, IRecord &r) {
    if(!isOpen()) {
        std::cerr << "Unable to read record, database currently closed" << std::endl;
        return false;
    }

    if ((0 <= recordNum) && (recordNum <= totalEntries))
    {
        f_db.seekg(recordNum * recordSize, std::ios::beg);
        std::string line;
        getline(f_db, line);
        if(!isBlankRecord(line)) {
            r.unmarshal(line);
        }
    } else {
        std::cerr << "Record out of range" << std::endl;
        return false;
    }
    return true;
}

bool Database::isBlankRecord(const std::string &line) {
    return stoi(line) == -1;
}

void Database::close() {
    f_db.close();
    std::cout << "Database Closed " << std::endl;
}

void Database::displayRecord(IRecord &r) {
    if(!isOpen()) {
        std::cerr << "Unable to read record, database currently closed" << std::endl;
        return;
    }

    f_db.seekg(std::ios::beg);
    std::string line;

    while(getline(f_db, line)) {
        if(isBlankRecord(line)) continue;
        r.unmarshal(line);
        r.print();
    }
}

