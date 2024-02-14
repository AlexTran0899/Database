//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

#include <iostream>
#include <fstream>
#include "PassengerInfo.h"

using namespace std;

class DB {
private:
    fstream f_db;
    ifstream f_csv;

public:
    int num_records;
    int record_size;
    DB();
    ~DB();

    bool openDb(const string &filename);
    bool createDB(const string &inFilename);
    void close();

    bool readRecord(string &status, const int RecordNum, PassengerInfo &data);
    bool binarySearch(const int Id, PassengerInfo& foundPassenger);
    bool displayRecord(string &status);
    bool checkIfRecordValid(string &line);
    bool isOpen();
};
