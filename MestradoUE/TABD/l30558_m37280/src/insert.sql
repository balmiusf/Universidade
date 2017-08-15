insert into books values(0, 'Fantastic Beasts', 'Fantasy');
insert into borrower values(0, 'Jonh');
insert into loan values(0, '0', '10-10-2012');
insert into books values(1, 'Eragon', 'Fantasy');
insert into borrower values(1, 'Paul');
insert into loan values(1, '1', '10-10-2013');
insert into books values(2, 'Rocky', 'History');
insert into borrower values(2, 'Rocky');
insert into loan values(2, '2', '10-10-2014');
insert into books values(3, 'Mistery', 'Drama');
insert into borrower values(3, 'Keith');
insert into loan values(3, '3', '10-10-2015');
insert into books values(4, 'He-Man', 'Kids');
insert into borrower values(4, 'McFly Jr');
insert into loan values(4, '4', '10-10-2020');
insert into books values(5, 'Hodor', 'Fantasy');
insert into borrower values(5, 'Jon Snow');
insert into loan values(5, '5', '10-10-1220');
insert into books values(6, 'Metro 2033', 'Ukranian');
insert into borrower values(6, 'Artyom');
insert into loan values(6, '6', '13-11-2033');
insert into books values(7, 'Civilization', 'Turn-Based');
insert into borrower values(7, 'Sid Meiers');
insert into loan values(7, '7', '10-10-2010');
insert into books values(8, 'Witcher', 'Fantasy');
insert into borrower values(8, 'CD Projekt');
insert into loan values(8, '8', '10-10-2017');
insert into books values(9, 'Sql for Dummies', 'Learning');
insert into borrower values(9, 'Joao S');
insert into loan values(9, '9', '21-05-2017');

update books set tile = 'Noddy' where category = 'Kids';
update loan set return_date = '21-05-2017' where isbn = '5';
 

delete from loan where isbn = 3;
delete from loan where return_date = '10-10-2010';
