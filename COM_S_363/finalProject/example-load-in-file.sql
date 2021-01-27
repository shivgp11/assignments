-- run forimport.sql
-- make sure that the file is named correctly.
-- for 2020 data, use ',' as the field terminator
-- for 2016 data, use ';' as the field terminator
-- for Linux, the line terminator may be different
-- 81906 rows are the correct number of rows to be imported
-- the REPLACE INTO TABLE is to empty the existing rows in the table before adding new rows.
-- the tweets.csv file must locate inside the specified folder.
-- find out where are the folder MySQL expects the data files to be.
-- to load data from a different folder beyond the default folder, MySQL server configuration file must be changed.

show variables like 'secure_file_priv';

use test;
LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/2016/tweets.csv' REPLACE INTO TABLE tweet
FIELDS TERMINATED BY ';' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
IGNORE 1 LINES
(tid,textbody,retweet_count,retweeted,posted,@col6);

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/2016/tweets.csv' REPLACE INTO TABLE newtweet
FIELDS TERMINATED BY ';' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
IGNORE 1 LINES
(tid,textbody,retweet_count,retweeted,@col5,@col6)
set day_posted= day(str_to_date(@col5, '%Y-%m-%d %H:%i:%s')), month_posted= month(str_to_date(@col5, '%Y-%m-%d %H:%i:%s')), year_posted= year(str_to_date(@col5, '%Y-%m-%d %H:%i:%s'));


