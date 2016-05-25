CREATE TABLE pessoa (
nome INT NOT NULL CHECK,
cpf VARCHAR,
fone INT,
PRIMARY KEY (cpf));

CREATE TABLE carro (
placa VARCHAR,
montadora VARCHAR,
chassi INT,
PRIMARY KEY (chassi));


SELECT * FROM carro;
SELECT nome FROM pessoa;
SELECT * FROM montadora;

