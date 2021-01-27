insert into group70.users 
select screen_name, name, num_followers, num_following, category, subcategory, state
from final_project.users;

insert into group70.tweets
select tid, text, retweet_count, created_time, user_screen_name
from final_project.tweets;

insert into group70.mentions
select tweet_tid, user_screen_name
from final_project.mentions;

insert into group70.hastags
select tweets_tid, hashtags_name
from final_project.hastags;

insert into group70.hasurls
select tweets_tid, urls_address
from final_project.hasurls;