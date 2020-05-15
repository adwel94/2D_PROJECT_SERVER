drop database GAME_DB;

create database GAME_DB;
use GAME_DB;

set SQL_SAFE_UPDATES=0;

drop table test_table;

create table test_table
(
a int,
b int,
c int
);



insert into test_table values(1,2,3);
insert into test_table values(2,4,6);
insert into test_table values(3,5,7);


create table user_table
(
mCode bigint,
mId char(30), 
mPw char(30),

primary key(mCode,mId)
);

select* from user_table;

insert into user_table values(1,'aa','bb');

create table charactor_table
(
mCode bigint,
mUser_Code bigint,
mName char(30), 
mJob int,

primary key(mCode,mName),
foreign key(mUser_Code) references user_table(mCode) on delete cascade
);

insert into charactor_table values(3,1,'nick',100);

select* from charactor_table;

insert into test_table values(3,5,7);

select * from charactor_table where mUser_Code = 1;

delete from charactor_table where mName='nick';
