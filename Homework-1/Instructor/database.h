#include <fstream>
using namespace std;

const int ID_SIZE = 7;
const int FIRST_SIZE = 12;
const int LAST_SIZE = 20;
const int AGE_SIZE = 3;
const int TICKET_NUM_SIZE = 20;
const int FARE_SIZE = 6;
const int DATE_SIZE = 10;

class Database
{
public:
   Database();
   ~Database();
   
   bool createDb(const string filename);
   bool openDb(const string filename); //this is open()
   void closeDb();
   bool isOpen();
   void writeRecord(string id, string first_name, string last_name, string age, 
				 string ticket_num, string fare, string purchase_date);
   bool readRecord(const int record_num, string &id, string &first_name, string &last_name, 
				 string &age, string &ticket_num, string &fare, string &purchase_date);
			   
   //variables
   const int static RECORD_SIZE = 85;

private:
   int num_records;
   int record_size;
   fstream f_db;
   ifstream f_csv;

   bool readCsv(string &id, string &firstName, string &lastName, string &age, string &ticketNum, string &fare, string &purchaseDate);
};
