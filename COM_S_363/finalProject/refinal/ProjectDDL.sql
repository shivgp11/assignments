/*
Schema:
- hashtags(name, primary key(name))
- urls(address, primary key(address))
- users(screen name, name, numFollowers, numFollowing, category, subcategory, state
	primary key(screen_name))
- tweets(tid, text, retweetCt, createdTime, posted_by, 
	primary key(tid), foreign key(posted_by) references users(screen_name) on delete cascade)
- mentions(tweet_tid, user_screen_name, 
	primary key(tid, user_screen_name), foreign key(tweets_tid) references tweets(tid), foreign key(user_screen_name)
    references users(screen_name))
- hasUrls (tweets_tid, urls_address, primary key(tweets_tid, urls_address), foreign key(tweets_tid) references tweets(tid), 
	foreign key(urls_address) references urls(address)
- hasTags (tweets_tid, hashtags_name, primary key(tweets_tid, hashtags_name), foreign key(tweets_tid) references tweets(tid), 
	foreign key(hashtags_name) references hashtags(name))
*/

drop database if exists group70;
create database if not exists group70;
use group70;

drop table if exists users;
create table users (
screen_name varchar(30), 
name varchar(30), 
num_followers int, 
num_following int, 
category varchar(30), 
subcategory varchar(30),
state varchar(30), 
primary key(screen_name)
);

drop table if exists tweets;
create table tweets (
tid bigint, 
text varchar(500), 
retweet_count int, 
created_time datetime, 
user_screen_name varchar(30) not null, 
primary key(tid), 
foreign key(user_screen_name) references users(screen_name) on delete cascade
);
 
 drop table if exists mentions;
 create table mentions (
 tweet_tid bigint, 
 user_screen_name varchar(30), 
 primary key(tweet_tid, user_screen_name), 
 foreign key(tweet_tid) references tweets(tid), 
 foreign key(user_screen_name) references users(screen_name)
 );
 
 drop table if exists hasUrls;
 create table hasUrls (
tweets_tid bigint, 
urls_address varchar(200), 
primary key(tweets_tid, urls_address), 
foreign key(tweets_tid) references tweets(tid)
); 

drop table if exists hasTags;
create table hasTags (
tweets_tid bigint, 
hashtags_name varchar(30),
primary key(tweets_tid, hashtags_name),
foreign key(tweets_tid) references tweets(tid)
);
