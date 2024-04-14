mysql <<EOFMYSQL
use phtran;
show tables;

DROP TABLE IF EXISTS FoodOrder;
DROP TABLE IF EXISTS MenuItem;
DROP TABLE IF EXISTS Dish;
DROP TABLE IF EXISTS Restaurant;

CREATE TABLE Restaurant(
 restaurantNo INTEGER PRIMARY KEY,
 restaurantName CHAR(15) NOT NULL,
 type CHAR(15) NOT NULL,
 city CHAR(15) NOT NULL
);

CREATE TABLE Dish(
 dishNo INTEGER PRIMARY KEY AUTO_INCREMENT,
 dishName CHAR(25) NOT NULL,
 type ENUM('ap','en','ds')
);

CREATE TABLE MenuItem(
 itemNo INTEGER PRIMARY KEY AUTO_INCREMENT,
 restaurantNo INTEGER NOT NULL,
 dishNo INTEGER,
 price DECIMAL(4,2) NOT NULL,
 FOREIGN KEY (restaurantNo) REFERENCES Restaurant(restaurantNo) ON DELETE RESTRICT,
 FOREIGN KEY (dishNo) REFERENCES Dish(dishNo) ON DELETE SET NULL,
 CONSTRAINT price_range CHECK (price >= 5 AND price <= 50)
);

CREATE TABLE FoodOrder(
 orderNo INTEGER PRIMARY KEY AUTO_INCREMENT,
 itemNo INTEGER NOT NULL,
 date DATE,
 time TIME,
 FOREIGN KEY (itemNo) REFERENCES MenuItem(itemNo) ON DELETE CASCADE,
 CONSTRAINT date_range CHECK(date >= '2024-01-01')
);

INSERT INTO Restaurant(restaurantNo, restaurantName, type, city) VALUES
(0, 'Tasty Thai', 'Asian', 'Dallas'),
(3, 'Eureka Pizza', 'Pizza', 'Fayetteville'),
(5, 'Tasty Thai', 'Asian', 'Las Vegas');

INSERT INTO Dish(dishNo, dishName, type) VALUES
(1, 'Spring Rolls', 'ap'),
(2, 'Pad Thai', 'en'),
(3, 'Pot Stickers', 'ap'),
(4, 'Masaman Curry', 'en'),
(5, 'Custard', 'ds'),
(6, 'Garlic Bread', 'ap'),
(7, 'Salad', 'ap'),
(8, 'Cheese Pizza', 'en'),
(9, 'Pepperoni Pizza', 'en'),
(10, 'Veggie Supreme Pizza', 'en');

INSERT INTO MenuItem (restaurantNo, dishNo, price) VALUES
(0, 1, 8.00),
(0, 3, 9.00),
(0, 7, 10.00),
(0, 2, 19.00),
(0, 4, 19.00),
(3, 7, 6.25),
(3, 6, 5.50),
(3, 8, 12.50),
(3, 9, 13.50),
(5, 1, 6.00),
(5, 2, 15.00),
(5, 4, 14.00);

INSERT INTO FoodOrder(itemNo, date, time) VALUES
( 3, '2024-03-01', '10:30'),
( 2, '2024-03-02', '15:33'),
( 4, '2024-03-01', '15:35'),
( 6, '2024-03-03', '21:00'),
( 8, '2024-03-01', '18:11'),
( 8, '2024-03-04', '18:51'),
( 10, '2024-03-01', '19:00'),
( 12, '2024-03-05', '17:15'),
( 12, '2024-04-01', '12:10');


EOFMYSQL

