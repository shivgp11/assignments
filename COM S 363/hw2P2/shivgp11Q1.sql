-- Author: Shiv Patel

-- a
select count(*) from ingredient;

-- b
select f.fid , f.fname
from ingredient i1 inner join recipe r1 on i1.iid = r1.iid
inner join food f on f.fid = r1.fid 
inner join recipe r2 on f.fid = r2.fid
inner join ingredient i2 on i2.iid = r2.iid and 
i1.iname = "Green Onion" and i2.iname = "Beef";

-- c
select i.iid, i.iname
from ingredient i left join recipe r 
on i.iid = r.iid
where r.fid is null
order by i.iid asc;

-- d
select f.fid, f.fname, count(r.iid) as count_ingredients, sum(r.amount) as total_amount
from food f inner join recipe r on f.fid = r.fid
group by f.fid 
order by count_ingredients desc;

-- e
select f.fid, f.fname, i.iid, i.iname, cast(r.amount * i.caloriepergram as float) as calories
from food f inner join recipe r on f.fid = r.fid 
inner join ingredient i on i.iid = r.iid
where r.fid in 
(select r.fid from recipe r inner join ingredient i on r.iid = i.iid where i.iname = "Chicken")
order by f.fid asc;

-- f
select f.fid, f.fname
from food f inner join recipe r on f.fid = r.fid
inner join ingredient i on i.iid = r.iid
where i.category = "Vegetable"
group by f.fid
having count(i.category) = 2 and sum(r.amount) > 5
order by f.fid desc;

