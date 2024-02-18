//
// Created by Alex Tran on 2/17/24.
//

#ifndef SELF_DATABASE_HPP
#define SELF_DATABASE_HPP

#include <string>
#include <fstream>
#include "./Interfaces/IRecord.hpp"

class Database {
private:
    unsigned long int recordCount;
    unsigned long int totalEntries;
    unsigned int recordSize;
    std::fstream f_db;

public:
    Database();
    ~Database();
    bool create(std::string &filename,IRecord &r);
    bool open(std::string &filename);
    void close();
    bool isOpen();

    bool isBlankRecord(const std::string &line);

    void displayRecord(IRecord &r);
    bool readRecord(unsigned int recordNum, IRecord &r);
    bool writeRecord();
    bool binarySearch();
    bool updateRecord();
    bool deleteRecord();
    bool addRecord();
};

#include "../Src/Database.cpp"

#endif //SELF_DATABASE_HPP
