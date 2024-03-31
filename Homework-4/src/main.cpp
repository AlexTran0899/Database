#include <iostream>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

int main() {
    try {
        // Initialize the driver
        sql::mysql::MySQL_Driver *driver;
        driver = sql::mysql::get_mysql_driver_instance();

        // Connect to the database
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", ""));

        // Select the MySQL database
        con->setSchema("database_name");

        // Execute a query
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 'Hello World!' AS _message"));

        // Iterate over the result set and print each message
        while (res->next()) {
            std::cout << res->getString("_message") << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return 0;
}
