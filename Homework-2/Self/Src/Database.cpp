//
// Created by Alex Tran on 2/17/24.
//

#include "Database.hpp"
#include <iostream>
#include <fstream>


Database::Database(std::shared_ptr<IRecord> record) {
    recordCount = 0;
    totalEntries = 0;
    recordSize = 0;
    this->record = std::move(record);
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



bool Database::isOpen() const {
    return f_db.is_open();
}


Database::~Database() {}


bool Database::create(std::string &filename) {
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
        record->parseString(line);
        record->marshal(f_db, true);
        record->marshal(f_db);
        recordCount += 1;
    }
    totalEntries += recordCount * 2;

    f_config << recordCount << std::setw(20) << totalEntries << std::setw(20) << record->getRecordSize() << std::endl;

    f_csv.close();
    f_db.close();
    f_config.close();
    return true;
};

bool Database::readRecord(int recordNum, std::shared_ptr<IRecord> rec) {
    if(!isOpen()) {
        std::cerr << "Unable to read record, database currently closed" << std::endl;
        return false;
    }

    rec->clear();
    if ((0 <= recordNum) && (recordNum <= totalEntries))
    {
        f_db.seekg(recordNum * recordSize, std::ios::beg);
        std::string line;
        getline(f_db, line);
        if(!Utils::isBlankRecord(line)) {
            rec->unmarshal(line);
            return true;
        }
    } else {
        std::cerr << "Record out of range: " << recordNum << std::endl;
    }
    return false;
}


void Database::close() {
    record = nullptr;
    f_db.close();
    std::cout << "Database Closed " << std::endl;
}

void Database::displayRecord(int id, std::shared_ptr<IRecord> rec) {
    if(!isOpen()) {
        std::cerr << "Unable to display record, database currently closed" << std::endl;
        return;
    }

    if(id < 0) {
        std::cerr << "ID should must be or larger than 0" << std::endl;
        return;
    }

    int entriesNumber = 0;
    binarySearch(id, entriesNumber,rec);
    rec->print();
}

bool Database::binarySearch(int id, int &entriesNumber, std::shared_ptr<IRecord> rec) {
    int l = 0;
    int r = totalEntries;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        int temp = mid;

        // assuming our entire database isn't filled with empty record
        int counter = 20;
        while(!readRecord(temp, rec) && counter > 0){
            temp += 1;
            counter -=1;
        }

        if (rec->getID() == id) {
            entriesNumber = temp;
            return true;
        } else if (rec->getID() > id) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    entriesNumber = l;
    rec->clear();
    return false;
}

bool Database::deleteRecord(int id, std::shared_ptr<IRecord> rec) {
    if(!isOpen()) {
        std::cerr << "Unable to delete record, database currently closed" << std::endl;
        return false;
    }

    int entriesNumber = 0;
    binarySearch(id, entriesNumber, rec);
    f_db.seekg(entriesNumber * recordSize, std::ios::beg);
    rec->marshal(f_db, true);
}

bool Database::updateRecord(const IRecord &rec) {
    if(!isOpen()) {
        std::cerr << "Unable to update record, database currently closed" << std::endl;
        return false;
    }
    int entriesNumber;
    bool founded = binarySearch(rec.getID(), entriesNumber, record);

    if(founded){
        f_db.seekg(entriesNumber * recordSize, std::ios::beg);
        rec.marshal(f_db);
        return true;
    } else {
        std::cerr << "Unable to update record, record not found" << std::endl;
    }
    return false;
}

bool Database::addRecord(const IRecord &rec) {
    if(!isOpen()) {
        std::cerr << "Unable to add record, database currently closed" << std::endl;
        return false;
    }
    int entriesNumber;
    bool founded = binarySearch(rec.getID(), entriesNumber, record);

    if(!founded){
        f_db.seekg(entriesNumber * recordSize, std::ios::beg);
        std::cout << "here in the add record method" << std::endl;

        rec.marshal(f_db);
    } else {
        std::cerr << "Entry with ID: " + std::to_string(rec.getID()) + " already exist in DB" << std::endl;
        record->print();
    }
}

bool Database::createReport(std::shared_ptr<IRecord> rec) {
    if(!isOpen()) {
        std::cerr << "Unable to create report, database currently closed" << std::endl;
        return false;
    }

    f_db.seekg(0, std::ios::beg);
    std::string line;

    int counter = 10;

    while(std::getline(f_db,line) && counter > 0){
        if(Utils::isBlankRecord(line)) continue;
        counter -= 1;
        rec->unmarshal(line);
        rec->print();
    }

    return counter == 0;
}