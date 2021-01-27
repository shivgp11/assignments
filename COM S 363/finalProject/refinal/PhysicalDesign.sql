-- Q3 - optimization method: increase buffer pool size
set global innodb_buffer_pool_size = 8388608*4;
-- set it back 
set global innodb_buffer_pool_size = 8388608;

-- Q7: - optimization method: create index
create index idx7 on hastags (hashtags_name, tweets_tid);
-- drop index 
drop index idx7 on hastags;

-- Q9: - optimization method: create index
create index idx9 on users (subcategory);
-- drop index
drop index idx9 on users;

-- Q16 - optimization method: increase buffer pool size
set global innodb_buffer_pool_size = 8388608*4;
-- set it back 
set global innodb_buffer_pool_size = 8388608;

-- Q18 - - optimization method: increase buffer pool size
set global innodb_buffer_pool_size = 8388608*4;
-- set it back 
set global innodb_buffer_pool_size = 8388608;

-- Q23:  - optimization method: create index
create index idx23 on tweets (tid, user_screen_name, created_time);
-- drop index 
drop index idx23 on tweets;