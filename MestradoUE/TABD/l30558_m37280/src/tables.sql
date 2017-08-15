--Script for creating database
--drop schema public cascade;
create schema public;
grant all on schema public to public;
	
CREATE DATABASE library_database andrefigueira --poe aqui o teu user;

--drop schema public cascade;

DROP TABLE IF EXISTS books CASCADE;
DROP TABLE IF EXISTS borrower CASCADE;
DROP TABLE IF EXISTS loan CASCADE;


CREATE TABLE books(
	isbn integer CONSTRAINT books_pkey PRIMARY KEY,
	tile varchar(40) NOT NULL,
	category varchar(20) NOT NULL
);

CREATE TABLE borrower(
	borrower_id integer CONSTRAINT borrower_pkey PRIMARY KEY,
	name varchar(20)
);

CREATE TABLE loan(
	borrower_id integer,
	isbn integer,
	return_date varchar(20),

	CONSTRAINT loan_pkey PRIMARY KEY(borrower_id, isbn),
	CONSTRAINT loan_fkey1 FOREIGN KEY(isbn) REFERENCES books(isbn),
	CONSTRAINT loan_fkey2 FOREIGN KEY(borrower_id) REFERENCES borrower(borrower_id)
);
