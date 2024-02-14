#include "DB.h"
#include "PassengerInfo.h"
#include <sstream>
#include <iomanip>

DB::DB()
{
    num_records = 0;
}

DB::~DB() {}

void DB::open(string filename)
{
    filename = filename + ".data";
    Din.open(filename.c_str(), fstream::in | fstream::out | fstream::app);
}

void DB::close()
{
    Din.close();
}

bool DB::findRecordByOffset(string &status, const int RecordNum, PassengerInfo &data)
{
    bool found = false;
    stringstream output;

    if ((0 <= RecordNum) && (RecordNum <= num_records))
    {
        Din.seekg(RecordNum * 100, ios::beg);
        string line = "-1";
        while(!checkIfRecordValid(line) && !Din.eof()) {
            getline(Din, line);
        }
        if(checkIfRecordValid(line)) {
            stringstream ss(line);
            PassengerInfo p;
            p.marshal(ss);
            data = p;
            found = true;
        }
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

        if (findRecordByOffset(status , middle, p))
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
            return false; // Error reading record
        }
    }
    return found;
}

void DB::createDB(const string inFilename) {
    ifstream Din;
    ofstream Dout;
    ofstream ConfigOut;

    string line = "";

    Din.open(inFilename + ".csv");
    Dout.open(inFilename + ".data");
    ConfigOut.open(inFilename + ".config");

    while (!Din.eof()) {
        getline(Din, line);
        PassengerInfo passenger =  PassengerInfo::parseData(line);
        passenger.unmarshal(Dout);
        passenger.saveBlankRecord(Dout);
        DB::num_records += 2;
    }

    ConfigOut << DB::num_records <<  setw(20) << DB::RECORD_SIZE << endl;
    ConfigOut.close();
    Din.close();
    Dout.close();
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

bool DB::displayRecord(string &status, string &inFilename){
    ifstream Din;
    ofstream ConfigOut;
    string line;

    Din.open(inFilename + ".data");
    while (!Din.eof()) {
        getline(Din, line);
        if(checkIfRecordValid(line)){
            PassengerInfo passenger = PassengerInfo();
            stringstream ss(line);
            passenger.marshal(ss);
            passenger.print();
        }
    }
    Din.close();
    return true;
};
