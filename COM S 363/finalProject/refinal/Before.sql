-- Q3: k = 5, year = 2016
select count(distinct state) as num_states, group_concat(distinct state) as states, hashtags_name
from users, tweets, hastags
where users.screen_name = tweets.user_screen_name and hastags.tweets_tid = tweets.tid and year(created_time) = 2016 and state not in (select state from users where state = "na")
group by hashtags_name
order by num_states desc
limit 5; 

-- Q7: k = 5, month = 2, year = 2016, state = NC, hashtag_name - "GOPDebate"
select count(tid), screen_name, category
from users, tweets, hastags
where users.screen_name = tweets.user_screen_name and hastags.tweets_tid = tweets.tid 
and month(created_time) = 2 and year(created_time) = 2016 and state = "NC" and hashtags_name = "GOPDebate"
group by screen_name
order by count(tid) desc
limit 5;

-- Q9: k = 5, subcategory = Democrat
select screen_name, subcategory, num_followers
from users 
where subcategory = "Democrat"
order by num_followers desc
limit 5;

-- Q16: k = 5, month = 2, year = 2016
select name, category, text, retweet_count, urls_address
from users, tweets, hasurls
where users.screen_name = tweets.user_screen_name and hasurls.tweets_tid = tweets.tid
and month(created_time) = 2 and year(created_time) = 2016
order by retweet_count desc
limit 5;

-- Q18: k = 5, subcategory = "GOP", month = 1, year = 2016
select mentions.user_screen_name, state, group_concat(distinct screen_name)
from users, mentions, tweets
where mentions.tweet_tid = tweets.tid and users.screen_name = tweets.user_screen_name 
and subcategory = "GOP" and month(created_time) = 1 and year(created_time) = 2016
group by mentions.user_screen_name
order by count(screen_name) desc
limit 5;

-- Q23: k = 5, subcategory = "GOP", year = 2016, month = [1,2,3]
select hashtags_name, count(tid)
from hastags, users, tweets
where hastags.tweets_tid = tweets.tid and users.screen_name = tweets.user_screen_name
and subcategory = "GOP" and year(created_time) = 2016 and find_in_set(month(created_time), "1,2,3")
group by hashtags_name
order by count(tid) desc
limit 5;


