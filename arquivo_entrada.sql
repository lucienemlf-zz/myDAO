CREATE TABLE person (
name INT NOT NULL CHECK,
cpf VARCHAR,
phone INT,
carrochassi INT,
PRIMARY KEY (cpf),
FOREIGN KEY (carrochassi) REFERENCES carro(chassi)
);

CREATE TABLE Car (
plate VARCHAR,
mounter VARCHAR,
chassi INT,
PRIMARY KEY (chassi)
);

SELECT cpf FROM person;

SELECT plate FROM Car;

SELECT mounter,chassi FROM Car;

SELECT name, cpf FROM person;
