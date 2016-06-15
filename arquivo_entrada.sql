CREATE TABLE person (
name INT NOT NULL CHECK,
cpf VARCHAR,
phone INT,
PRIMARY KEY (cpf)
);

CREATE TABLE Car (
plate VARCHAR,
mounter VARCHAR,
chassi INT,
PRIMARY KEY (chassi)
);

SELECT name,cpf FROM person;

SELECT mounter,chassi,blablabla FROM Car;

SELECT * FROM pessoa;
