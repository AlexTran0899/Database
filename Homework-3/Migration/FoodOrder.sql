CREATE TABLE FoodOrder(
orderNo INTEGER PRIMARY KEY,
itemNo INTEGER NOT NULL,
date DATE,
time TIME,
FOREIGN KEY (itemNo) REFERENCES MenuItem(itemNo) ON DELETE CASCADE,
CONSTRAINT date_range CHECK(date >= '2024-01-01')
);