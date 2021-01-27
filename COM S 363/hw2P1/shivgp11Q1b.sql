-- Author Shiv Patel

/* Schema: 
	-Patient(ssn int, address varchar(40), name varchar(40), dateofbirth date, doctor_id int not null, 
	primary key(ssn), foreign key(doctor_id) references Doctor(id))
    
	-Prescription(order_date date, quantity int, primary key(orderdate))
    
	-Drug(trade_name varchar(40), formula varchar(100), pham_co_name varchar(40) not null, 
	primary key(trade_name, pham_co_name), foreign key(pham_co_name) references Pham_Co(name) on delete cascade)
    
	-Pham_Co(name varchar(40), address varchar(40), license_no int, primary key(name))
    
	-Personnel(id int, name varchar(40), phone_number int, salary int, primary key(id))
    
	-Doctor_Nurse(id int, specialty varchar(40), recent_education varchar(40), employee_type varchar(40),
	primary key(id), foreign key(id) references Personnel(id) on delete cascade)
    
	-Administrator(id int, role varchar(40), primary key(id), foreign key(id) references Personnel(id) on delete cascade)

    
	-Mentoring(mentor_id int, mentee_id int, primary key(mentor_id, mentee_id), 
	foreign key(mentor_id) references Doctor_Nurse(id), foreign key(mentee_id) references Doctor_Nurse(id))
    
	-Prescribed(patient_ssn int, order_date date, doctor_id int, trade_name varchar(40), pham_co_name varchar(40),
	primary key(patient_ssn, order_date, doctor_id, trade_name, pham_co_name), 
	foreign key(patient_ssn) references Patient(ssn), foreign key (order_date) references Prescription(order_date), 
	foreign key(doctor_id) references Doctor(id), 
	foreign key (trade_name, pham_co_name) references Drug(trade_name, pham_co_name))
	
*/

drop database if exists shivgp11;
create database if not exists shivgp11;
use shivgp11;

drop table if exists Personnel;
create table Personnel(
id int, 
name varchar(40), 
pho_number varchar(40),
salary int, 
primary key(id)
);


drop table if exists Doctor_Nurse;
create table Doctor_Nurse(
id int, 
specialty varchar(40), 
recent_edu varchar(40),
employee_type varchar(40),
primary key(id),
foreign key(id) references Personnel(id) on delete cascade
);

drop table if exists Mentoring;
create table mentoring (
mentor_id int, 
mentee_id int, 
primary key(mentor_id, mentee_id),
foreign key(mentor_id) references doctor_nurse(id), 
foreign key(mentee_id) references doctor_nurse(id)
);

drop table if exists Administrator;
create table Administrator(
id int,
role varchar(40),
primary key(id),
foreign key(id) references Personnel(id) on delete cascade
);

drop table if exists Patient;
create table Patient(
ssn varchar(40), 
address varchar(40),
name varchar(40),
bdate date,
primary_phys_id int not null,
primary key(ssn), 
foreign key(primary_phys_id) references Doctor_Nurse(id) 
);

drop table if exists Pharm_Co;
create table Pharm_Co(
name varchar(40),
address varchar(40),
license_no varchar(40), 
primary key(name)
);

drop table if exists Drug;
create table Drug(
trade_name varchar(40),
formula varchar(40),
pharm_co_name varchar(40) not null,
primary key(trade_name, pharm_co_name),
foreign key(pharm_co_name) references Pharm_Co(name) on delete cascade on update cascade
);

drop table if exists Prescription;
create table Prescription(
order_date date,
quantity int,
primary key(order_date)
);

drop table if exists Prescribed;
create table Prescribed(
patient_ssn varchar(40), 
doctor_id int,
order_date date, 
trade_name varchar(40),
pharm_co_name varchar(40),
primary key(patient_ssn, order_date, doctor_id, trade_name, pharm_co_name),
foreign key(patient_ssn) references Patient(ssn),
foreign key(doctor_id) references Doctor_Nurse(id),
foreign key(order_date) references Prescription(order_date), 
foreign key(trade_name, pharm_co_name) references Drug(trade_name, pharm_co_name)
);







