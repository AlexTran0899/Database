// DO:  more ~username/.my.cnf to see your password
// CHANGE:  MYUSERNAME and MYMYSQLPASSWORD in the main function to your username and mysql password
// COMPILE AND RUN:      ./compileandruncpp.sh

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <ctime>
#include <string>

using namespace std;
 
sql::Driver *driver;
sql::Connection *con;
sql::Statement *statement;
sql::ResultSet *resultSet;
sql::ResultSetMetaData *metaData;
sql::Connection* Connect(string, string);
 
void insert(string table, string tableValue ,string values);
void initDatabase(const string Username, const string Password, const string SchemaName);
sql::ResultSet * query (string q);
void print (sql::ResultSet *resultSet);
void disconnect();
void printRecords(sql::ResultSet *resultSet, int numColumns);
void printHeader(sql::ResultSetMetaData *metaData, int numColumns);
void insertIntoFoodOrderTable(string itemNo);
void findAllDishesAtAParticularRestaurant();
void listAllFoodOrdersForAParticularRestaurant();
void addANewDishForARestaurant();
void cancelAFoodOrder();
sql::ResultSet * getLastInsertedItem();

void printMenu() {
    cout << " 1: Find all available menu items at a given restaurant" << endl;
    cout << " 2: Order an available menu item from a particular restaurant" << endl;
    cout << " 3: List all food orders for a particular restaurant" << endl;
    cout << " 4: Cancel a food order" << endl;
    cout << " 5: Add a new dish for a restaurant" << endl;
    cout << "-1: Quit" << endl;
    cout << "Please enter a number: ";
}

void findAllDishesAtAParticularRestaurant() {
    cout << "Find all dishes at a particular restaurant" << endl;
    query("SELECT * FROM Restaurant");
    string restaurantName;
    cout << "Please enter the restaurant name" << endl;
    getline(cin, restaurantName);
    string restaurantCity;
    cout << "Please enter the restaurant city" << endl;   
    getline(cin, restaurantCity);

    string selectString = "SELECT d.dishName, m.price";
    string joinString = " FROM Restaurant as r JOIN MenuItem as m ON r.restaurantNo = m.restaurantNo JOIN Dish as d ON m.dishNo = d.dishNo";
    string conditionalString = " WHERE r.restaurantName = '" + restaurantName + "' AND " + "r.city = "+ "'" + restaurantCity + "';"; 
    string queryString = selectString + joinString + conditionalString;
    cout << queryString;
    sql::ResultSet * restaurantResult = query(queryString);

    if(restaurantResult->getRow() == 0) {  
        cout << "no dish founded for this restaurant :(" << endl;
    }

}

void orderItem(){
    query("SELECT * FROM Dish ");
    cout << "Please enter a dish name" << endl;
    string dishName;
    getline(cin, dishName);
    cout << dishName;

    string queryString = "SELECT itemNo, restaurantName, city, price FROM MenuItem as m NATURAL JOIN Dish LEFT JOIN Restaurant as r ON r.restaurantNo = m.restaurantNo  WHERE dishName = '" + dishName + "'";

    sql::ResultSet * queryResult = query(queryString);

    if(queryResult->getRow() == 0) {  
        cout << "dish not found :(" << endl;
        return;
    }

    string itemNo;
    cout << "Please enter an item number" << endl;
    getline(cin, itemNo);
    insertIntoFoodOrderTable(itemNo);
    query("SELECT * FROM FoodOrder");
    cout << endl;
}

void listAllFoodOrdersForAParticularRestaurant() {
    query("SELECT * FROM Restaurant");
    cout << "Please enter the restaurant name" << endl;
    string restaurantName;
    getline(cin, restaurantName);
    string city;
    cout << "Please enter the restaurant city" << endl;
    getline(cin, city);
    string queryString = "SELECT Dish.dishName, MenuItem.price, FoodOrder.date, FoodOrder.time FROM FoodOrder INNER JOIN MenuItem ON FoodOrder.itemNo = MenuItem.itemNo INNER JOIN Dish ON MenuItem.dishNo = Dish.dishNo INNER JOIN Restaurant ON MenuItem.restaurantNo = Restaurant.restaurantNo WHERE restaurantName = '" + restaurantName +"'" + " AND city = '" + city + "'";
    sql::ResultSet * restaurantResult = query(queryString);

    if(restaurantResult->getRow() == 0) {  
        cout << "no order founded :(" << endl;
    }

}

void insertIntoFoodOrderTable(string itemNo){
    // Get current time
    time_t currentTime = std::time(nullptr);
    
    // Convert time to local time
    tm* localTime = std::localtime(&currentTime);
    
    // Extract date components
    int year = localTime->tm_year + 1900; // years since 1900
    int month = localTime->tm_mon + 1;    // months since January (0-based)
    int day = localTime->tm_mday;         // day of the month
    
    // Define a buffer to hold the formatted time
    char formatedTime[80];
    
    // Format the time as a string
    std::strftime(formatedTime, sizeof(formatedTime), "%H:%M", localTime);
    
    // Output the current date
    string date =  to_string(year) + '-' + to_string(month) + '-' + to_string(day);

    string values =  "'" + itemNo + "','" + date + "','" + formatedTime + "'"; 
    insert ("FoodOrder", "itemNo, date, time", values); 
}

void cancelAFoodOrder() {
    query("SELECT f.orderNo, d.dishName, r.restaurantName, f.date, f.time FROM FoodOrder as f JOIN MenuItem as m ON f.itemNo = m.itemNo JOIN Dish as d ON m.dishNo = d.dishNo JOIN Restaurant as r ON m.restaurantNo = r.restaurantNo");
    cout << endl;
    string orderNo;
    cout << "Please enter an order number to cancel" << endl;
    getline(cin, orderNo);
    statement->executeUpdate("DELETE FROM FoodOrder WHERE orderNo = '" + orderNo + "';");
    query("SELECT f.orderNo, d.dishName, r.restaurantName, f.date, f.time FROM FoodOrder as f JOIN MenuItem as m ON f.itemNo = m.itemNo JOIN Dish as d ON m.dishNo = d.dishNo JOIN Restaurant as r ON m.restaurantNo = r.restaurantNo");
    cout << endl;
}

void addANewDishForARestaurant(){
    findAllDishesAtAParticularRestaurant();
    
    string restaurantNo = "0";

    cout << "add a new dish to a restaurant" << endl;

    string dishName;
    cout << "Please enter the dish name" << endl;
    getline(cin, dishName);

    string type;
    cout << "Please enter the dish type(en, ap, ds)" << endl;
    getline(cin, type);

    string price;
    cout << "Please enter the dish price: " << endl;
    getline(cin, price);

    string values =  "'" + dishName + "','" + type + "'"; 
    
    insert("Dish", "dishName, type", values); 

    // sql::ResultSet * latestDish = statement->executeQuery("SELECT * FROM Dish ORDER BY DESC LIMIT 1");

    string dishNo = "11";

    values = "0,'" + dishNo + "','" + price + "'"; 
    insert("MenuItem", "restaurantNo, dishNo, price", values); 

    findAllDishesAtAParticularRestaurant();
}


int main() 
{
    string Username = "phtran";          // Change to your own username
    string mysqlPassword = "xahcohC3";   // Change to your own mysql password
    string selection = "";

    initDatabase(Username, mysqlPassword, Username); //init and testing - use it to enter your queries

    while(selection != "-1") {
        printMenu();
        getline(cin, selection);
        int value = stoi(selection);
        
        switch(value){
            case 1:
                findAllDishesAtAParticularRestaurant();
                break;
            case 2:
                orderItem();
                break;
            case 3:
                listAllFoodOrdersForAParticularRestaurant();
                break;
            case 4:
                cancelAFoodOrder();
                break;
            case 5:
                addANewDishForARestaurant();
                break;
            case 6:
                disconnect();
                break;
            default:
                cout << "unknown command" << endl;
        }
    }

    cout << "\nTesting select:\n";

    // cout << "\nTesting insert of dept MATH:\n";
    // insert ("DEPT", "'MATH', 'Mathematics', 309, 'SCEN'"); 
    // query("SELECT * FROM DEPT WHERE DEPT_CODE = 'MATH';");

    // cout << "\nTesting delete of dept MATH:";
    // statement->executeUpdate("DELETE FROM DEPT WHERE DEPT_CODE = 'MATH';");
    // query("SELECT * FROM DEPT WHERE DEPT_CODE = 'MATH';");

    // cout << "\nTesting update of professor name:";
    // query("SELECT * FROM PROFESSOR WHERE PROF_ID = 123456;");
    // statement->executeUpdate("Update PROFESSOR set PROF_NAME = 'Susan Dyer' WHERE PROF_ID = 123456;");
    // query("SELECT * FROM PROFESSOR WHERE PROF_ID = 123456;");    

    disconnect();   
}   

// Connect to the database
sql::Connection* Connect(const string Username, const string Password)
 {
	 try{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", Username, Password);
		}
		 
	catch (sql::SQLException &e) {
        cout << "ERROR: SQLException in " << __FILE__;
        cout << " (" << __func__<< ") on line " << __LINE__ << endl;
        cout << "ERROR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        }
   return con;
}

// Disconnect from the database
void disconnect()
{
		delete resultSet;
		delete statement;
		con -> close();
		delete con;
} 

// Execute an SQL query passed in as a string parameter
// and print the resulting relation
sql::ResultSet * query (string q)
{
        try {
            resultSet = statement->executeQuery(q);
            cout<<("---------------------------------\n");
            cout<<("Query: \n" + q + "\n\nResult: \n");
            print(resultSet);
            return resultSet;
        }
        catch (sql::SQLException e) {
            cout << "ERROR: SQLException in " << __FILE__;
            cout << " (" << __func__<< ") on line " << __LINE__ << endl;
            cout << "ERROR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << ")" << endl;
            return nullptr;
        }
}
 
// Print the results of a query with attribute names on the first line
// Followed by the tuples, one per line
void print (sql::ResultSet *resultSet) 
{
    try{
		if (resultSet -> rowsCount() != 0)
		{
   		   sql::ResultSetMetaData *metaData = resultSet->getMetaData();
           int numColumns = metaData->getColumnCount();
		   printHeader( metaData, numColumns);
           printRecords( resultSet, numColumns);
		}
        else
			throw runtime_error("ResultSetMetaData FAILURE - no records in the result set");
    }
	catch (std::runtime_error &e) {
    }
}	

// Print the attribute names
void printHeader(sql::ResultSetMetaData *metaData, int numColumns)
{    
	/*Printing Column names*/  
    for (int i = 1; i <= numColumns; i++) {
            if (i > 1)
                cout<<",  ";
            cout<< metaData->getColumnLabel(i); //ColumnName
        }
        cout<<endl;
}		

// Print the attribute values for all tuples in the result
void printRecords(sql::ResultSet *resultSet, int numColumns)   
{ 
        while (resultSet->next()) {
            for (int i = 1; i <= numColumns; i++) {
                if (i > 1)
                    cout<<",  ";
                cout<< resultSet->getString(i);
               ;
            }
        cout<<endl;
        }
}

// Insert into any table, any values from data passed in as String parameters
void insert(string table, string tableValue, string values ) 
{
    string query = "";
    if(tableValue == "") {
        query = "INSERT into " + table + " values (" + values + ")";
    } else {
        query = "INSERT into " + table + "(" + tableValue + ")" + " values (" + values + ")";
        cout << query << endl;
    }
    statement->executeUpdate(query);
}



// init and  testing
// Assumes that the tables are already created
void initDatabase(const string Username, const string Password, const string SchemaName) 
{
        // Create a connection 
        con = Connect (Username, Password);
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", Username, Password);

        // Connect to the MySQL test database 
        con->setSchema(SchemaName);
 
        // Create a MYSQL statement to hold queries
        statement = con->createStatement();
}

