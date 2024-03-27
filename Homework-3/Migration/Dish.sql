CREATE TABLE Dish(
dishNo INTEGER PRIMARY KEY,
dishName CHAR(25) NOT NULL,
type ENUM('ap','en','ds')
);