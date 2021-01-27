-- SQL Script for Generating Kitchen Database
-- Authors: Randy PatanasakPinyo and W. Tavanapong

drop database if exists kitchen;
create database kitchen;
use kitchen;
drop table if exists recipe; 

drop table if exists food;
create table food 
(fid int, 
 fname varchar(45) not null unique,
 primary key(fid));

drop table if exists ingredient; 
create table ingredient
 (iid int, 
 iname varchar(45) not null unique,
 caloriepergram float,
 category varchar(20),
 primary key(iid)
 );

create table recipe (
  fid int,
  iid int,
  amount int not null,
  primary key(fid,iid),
  foreign key(fid) references food(fid),
  foreign key(iid) references ingredient(iid)
 );
 
INSERT INTO `food` VALUES (1,'Fried Rice'),(2,'Orange Chicken'),(3,'BBQ Pork'),(4,'BBQ Chicken'),(5,'Fried Noodle'),(6,'Mongolian Beef');

INSERT INTO `ingredient` VALUES(21,'Pork', 1.44, 'Meat'),(23,'Chicken', 1.65, 'Meat'),(24,'Orange', 0.47, 'Vegetable'),(28,'Green Onion', 0.10, 'Vegetable'),(29,'Egg Noodle', 2.0, 'Carbohydrate'),(31,'Beef', 1.8, 'Meat'),(32,'Cilantro',0.10,'Vegetable'),(33,'Carrot', 0.10, 'Vegetable'),(34,'Green Pepper', 1.00, 'Vegetable');

INSERT INTO `recipe` VALUES (1, 21, 10), (2,23,60),(2,24,30),(3,21,60),(4,23,6),(5,23,200),(5,28,60),(5,29,6),(6,28,5),(6,31,60),(1,32,3),(1,33,3),(4,32,1),(6,32,3);

