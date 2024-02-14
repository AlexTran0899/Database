#include "DB.h"
#include "PassengerInfo.h"
#include <sstream>
#include <iomanip>

DB::DB()
{
    num_records = 0;
}

DB::~DB() {}

void DB::close()
{
    f_db.close();
}

bool DB::openDb(const string &filename) {
    bool Success = false;
    if(isOpen()) {
        cout << "There is a database open already.   Please close that first." << endl;
        return false;
    }
    ifstream f_cfg;
    f_db.open(filename+".data");
    f_cfg.open(filename+".config");
    if (!f_cfg || !f_db){
        cerr << "Failed to open configuration file, openDb." << endl;
        return false;
    }

    f_cfg >> num_records >> record_size;
    f_cfg.close();
    Success = true;

    return Success;
}

bool DB::readRecord(string &status, const int RecordNum, PassengerInfo &data)
{
    bool found = false;
    stringstream output;

    if ((0 <= RecordNum) && (RecordNum <= num_records))
    {
        f_db.seekg(RecordNum * 100, ios::beg);
        string line = "-1";
        getline(f_db, line);
        if(!checkIfRecordValid(line)) {
            status = "Empty record";
            return found;
        }
        stringstream ss(line);
        PassengerInfo p;
        p.marshal(ss);
        data = p;
        found = true;
    }
    else
    {
        status = "Record " + to_string(RecordNum) + " out of range.";
    }
    return found;
}

bool DB::binarySearch(const int Id, PassengerInfo& foundPassenger)
{
    int Low = 0;
    int High = num_records - 1;
    bool found = false;

    while (!found && High >= Low)
    {
        int middle = (Low + High) / 2;
        string status;
        PassengerInfo p;

        if (readRecord(status, middle, p))
        {
            if (p.getPassengerId() == Id)
            {
                foundPassenger = p;
                found = true;
            }
            else if (p.getPassengerId() < Id)
                Low = middle + 1;
            else
                High = middle - 1;
        }
        else
        {
            return false;
        }
    }
    return found;
}

bool DB::createDB(const string &inFilename) {
    string line = "";
    f_csv.open(inFilename + ".csv");
    if (!f_csv){
        cerr << "Failed to open csv file" << endl;
        return false;
    }

    f_db.open(inFilename + ".data");
    if(!f_db) {
        cerr << "Unable to open DB" << endl;
        return false;
    }
    num_records = 0;

    getline(f_csv, line);

    while (!f_csv.eof()) {
        getline(f_csv, line);
        PassengerInfo passenger = PassengerInfo::parseData(line);
        passenger.unmarshal(f_db);
        passenger.saveBlankRecord(f_db);
        DB::num_records += 2;
    }

    ofstream ConfigOut;
    ConfigOut.open(inFilename + ".config");
    if(!ConfigOut) {
        cerr << "Failed to create configuration file" << endl;
    } else {
        ConfigOut << DB::num_records <<  setw(20) << DB::record_size << endl;
    }
    ConfigOut.close();
    f_csv.close();
}

bool DB::checkIfRecordValid(string &line){
    try {
        if(stoi(line) != -1) {
            return true;
        }
    } catch (exception e) {
        return false;
    }
    return false;
};

bool DB::displayRecord(string &status){
    ofstream ConfigOut;
    string line;

    if(!isOpen()) {
        status = "Database not open";
        return false;
    }

    while (!f_db.eof()) {
        getline(f_db, line);
        if(checkIfRecordValid(line)){
            PassengerInfo passenger = PassengerInfo();
            stringstream ss(line);
            passenger.marshal(ss);
            passenger.print();
        }
    }
    f_db.close();
    return true;
};

bool DB::isOpen()
{
    return f_db.is_open();
}

