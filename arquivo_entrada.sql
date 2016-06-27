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

SELECT mounter,chassi FROM Car;
