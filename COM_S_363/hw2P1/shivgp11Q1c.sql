-- Author Shiv Patel

use shivgp11;
set foreign_key_checks = 0;

truncate Personnel;
insert into Personnel values (1, "Shiv", "111-111-1111", 1000000);
insert into Personnel values (2,"Tyler", "222-222-2222", 2000000);
insert into Personnel values (3, "Tom", "333-333-3333", 3000000);
insert into Personnel values (4, "Cen", "444-444-4444", 4000000);


truncate Doctor_Nurse;
insert into Doctor_Nurse values(1, "neuro-surgery", null, "D");
insert into Doctor_Nurse values(2, "anesthesia", null, "D");
insert into Doctor_Nurse values(3, null, "Harper College", "N");
insert into Doctor_Nurse values(4, "ortho-surgery", null, "D");


truncate Mentoring;
insert into Mentoring values (1, 2);
insert into Mentoring values (1, 4);
insert into Mentoring values (2, 4);

truncate Administrator;
insert into Administrator values(1, "Director");
insert into Administrator values(2, "HR");
insert into Administrator values(3, "Treasurer");

truncate Patient;
insert into Patient values("111-11-1111", "Vietnam", "Tien", "2020-09-17", 1);
insert into Patient values("222-22-2222", "Sri Lanka", "Akhil", "2020-09-17", 1);
insert into Patient values("333-33-3333", "Malaysia", "Francis", "2020-09-17", 1);

truncate Pharm_Co;
insert into Pharm_Co values ("Drug America", "Des Mois", "ABC123");
insert into Pharm_Co values ("Drug India", "New Dheli", "DEF456");
insert into Pharm_Co values ("Drug Britain", "London", "GHI789");

truncate Drug;
insert into Drug values ("CVS", "F1", "Drug America");
insert into Drug values ("Walgreens", "F2", "Drug India");
insert into Drug values ("Black Market", "F3", "Drug Britain");

truncate Prescription;
insert into Prescription values ("2020-09-17", 1);
insert into Prescription values ("2020-09-16", 1);
insert into Prescription values ("2020-09-15", 1);

truncate Prescribed;
insert into Prescribed values ("111-11-1111", 1, "2020-09-17", "CVS", "Drug America");
insert into Prescribed values ("222-22-2222", 1, "2020-09-16", "Walgreens", "Drug India");
insert into Prescribed values ("333-33-3333", 1, "2020-09-15", "Black Market", "Drug Britain");

/*
select * 
from Personnel;

select *
from mentoring;

select * 
from Doctor_Nurse;

select * 
from Administrator;

select *
from Patient;

select * 
from Pharm_Co;

select *
from Drug;

select *
from Prescription;

select *
from Prescribed;
*/
