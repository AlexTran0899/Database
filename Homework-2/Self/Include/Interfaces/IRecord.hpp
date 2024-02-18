//
// Created by Alex Tran on 2/17/24.
//

#ifndef SELF_IRECORD_HPP
#define SELF_IRECORD_HPP

#include <iostream>
#include <fstream>
#include <string>

class IRecord {
private:
    int recordSize = 0;
public:
    virtual ~IRecord() {}

    virtual void marshal(std::ofstream &out, bool saveBlankRecord = false) const = 0;
    virtual void unmarshal(const std::string &line) = 0;
    virtual void parseString(const std::string &line) = 0;
    virtual void print() const = 0;
    virtual int getRecordSize() const = 0;
};


#endif //SELF_IRECORD_HPP
