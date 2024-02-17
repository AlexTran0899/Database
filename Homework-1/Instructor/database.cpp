#include <iomanip>
#include <iostream>
#include <algorithm>
#include "database.h"
using namespace std;

Database::Database()
{
	num_records = -1;
    record_size = -1;
}

Database::~Database()
{
}

bool Database::createDb(const string filename)
{
	/////////////////////////////////////possible strings might need to be set to an initial value
	string id, first_name, last_name, age, ticket_num, fare, purchase_date;

    // open csv file for reading
    f_csv.open(filename+".csv");
	if (!f_csv){
		cerr << "Failed to open csv file" << endl;
		return false;
    }

    // open data file for writing
	f_db.open(filename+".data", f_db.out);
    if (!f_db)
    {
		cerr << "Failed to open data file" << endl;
		return false;
    }

    // files are open
    num_records = 0;
	while(readCsv(id, first_name, last_name, age, ticket_num, fare, purchase_date))
	{
		writeRecord(id, first_name, last_name, age, ticket_num, fare, purchase_date);
        num_records++;
		writeRecord("_empty_", "None", "None", "None", "None", "None", "None");
        num_records++;
	}
	
	f_csv.close();
	f_db.close();
	
	//config file section
	ofstream f_cfg;
	f_cfg.open(filename+".config");
	if (!f_cfg)
		cerr << "Failed to create configuration file." << endl;
	else
	{
		f_cfg << num_records << " " << RECORD_SIZE << endl;
	}
	f_cfg.close();
	return true;
}

bool Database::openDb(const string filename)
{
bool Success = false;

    if (isOpen())
       cout << "There is a database open already.   Please close that first." << endl;
    else
    {
	   //read config file and set values
	   ifstream f_cfg;
   	
	   f_db.open(filename+".data");
	   f_cfg.open(filename+".config");
   	
	   if (!f_cfg || !f_db)
		   cerr << "Failed to open configuration file, openDb." << endl;
	   else
	   {
		  f_cfg >> num_records >> record_size;
	      f_cfg.close();
	      Success = true;
	   }
    }
    return Success;
}

void Database::closeDb()
{
	//does not say to update the config file here, might be a good idea to add it in
	if (isOpen()){
		f_db.close();
		num_records = -1;
		cout << "Database closed." << endl;
	}
	else{
		cout << "No database is open." << endl;
	}
}

bool Database::readCsv(string &id, string &firstName, string &lastName, string &age, string &ticketNum, string &fare, string &purchaseDate)
{
	if(getline(f_csv, id, ','))
	{
		getline(f_csv, firstName, ',');
		getline(f_csv, lastName, ',');
		getline(f_csv, age, ',');
		getline(f_csv, ticketNum, ',');
		getline(f_csv, fare, ',');
		getline(f_csv, purchaseDate);
		return true;
	}
	else
		return false;
}

void Database::writeRecord(string id, string first_name, string last_name, string age, 
						   string ticket_num, string fare, string purchase_date)
{

    // replace spaces with _
    replace(first_name.begin(), first_name.end(), ' ', '_');
    replace(last_name.begin(), last_name.end(), ' ', '_');
    replace(ticket_num.begin(), ticket_num.end(), ' ', '_');

	//do formatted writes
	f_db << setw(ID_SIZE) << left << id.substr(0, ID_SIZE) << " " 
         << setw(FIRST_SIZE) << left << first_name.substr(0, FIRST_SIZE) << " " 
         << setw(LAST_SIZE) << left << last_name.substr(0, LAST_SIZE) << " " 
         << setw(AGE_SIZE) << left << age.substr(0, AGE_SIZE) << " " 
         << setw(TICKET_NUM_SIZE) << left << ticket_num.substr(0, TICKET_NUM_SIZE) << " " 
         << setw(FARE_SIZE) << left << fare.substr(0, FARE_SIZE) << " " 
         << setw(DATE_SIZE) << left << purchase_date.substr(0, DATE_SIZE) << endl;
}


bool Database::readRecord(const int record_num, string &id, string &first_name, string &last_name, 
						 string &age, string &ticket_num, string &fare, string &purchase_date)
{
bool Success = false;

	if (!isOpen())
		cout <<"No Database open" << endl;
	else if ((record_num < 0) || (record_num >= num_records))
		cout << "value is out of range" << endl << endl;
    else
    {
	   f_db.seekg(((record_num) * record_size), ios::beg);
       f_db >> id >> first_name >> last_name >> age >> ticket_num >> fare >> purchase_date;
       Success = true;
    }
		
	return Success;
}
 
bool Database::isOpen()
{
   return f_db.is_open();
} 
