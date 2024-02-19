//
// Created by Alex Tran on 2/17/24.
//

#ifndef SELF_DATABASE_HPP
#define SELF_DATABASE_HPP

#include <string>
#include <fstream>
#include "./Interface/IRecord.hpp"

class Database {
private:
    unsigned long int recordCount;
    unsigned long int totalEntries;
    int recordSize;
    std::fstream f_db;
    std::shared_ptr<IRecord> record;


public:
    Database(std::shared_ptr<IRecord> record);
    ~Database();
    bool create(std::string &filename);
    bool open(std::string &filename);
    void close();
    bool isOpen() const;

    bool readRecord(int recordNum, std::shared_ptr<IRecord> rec); // need to MakeFile this public for testing in main but this should be private.
    void displayRecord(int id, std::shared_ptr<IRecord> rec);
    bool createReport(std::shared_ptr<IRecord> rec);
    bool binarySearch(int id, int &entriesNumber,std::shared_ptr<IRecord> rec);
    bool updateRecord(const IRecord &rec);
    bool deleteRecord(int id, std::shared_ptr<IRecord> rec);
    bool addRecord(const IRecord &rec);
};

#include "../Src/Database.cpp"

#endif //SELF_DATABASE_HPP
