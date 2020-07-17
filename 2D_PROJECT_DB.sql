create database GAME_DB;
use GAME_DB;

set SQL_SAFE_UPDATES=0;

create table user_table
(
mCode bigint unsigned,
mId char(30) unique, 
mPw char(30),

primary key(mCode)
);

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

