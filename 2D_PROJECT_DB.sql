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
mCode bigint unsigned,
mId char(30) unique, 
mPw char(30),

primary key(mCode)
);

drop table user_table;

drop table charactor_table;

select* from user_table;

insert into user_table values(10,'ss','bb');

create table charactor_table
(
mCode bigint unsigned,
mUser_Code bigint unsigned,
mName char(30) unique, 
mJob int,
mLevel int,

primary key(mCode),
foreign key(mUser_Code) references user_table(mCode) on delete cascade
);

alter table charactor_table add mLevel int;

insert into charactor_table values(1,1,'nick1',100);
insert into charactor_table values(2,1,'nick2',100);
insert into charactor_table values(3,1,'nick3',100);

select* from charactor_table;

SET SQL_SAFE_UPDATES =0;

update charactor_table set mLevel = 1;

insert into test_table values(3,5,7);

select * from charactor_table where mUser_Code = 1;

delete from charactor_table where mName='nick';
