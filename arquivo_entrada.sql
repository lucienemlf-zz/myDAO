CREATE TABLE pessoa (
Nome INT NOT NULL CHECK,
cpf VARCHAR,
fone INT,
PRIMARY KEY (rg)
);

CREATE TABLE carro (
placa VARCHAR,
montadora VARCHAR,
chassi INT,
PRIMARY KEY (chassi)
);

SELECT * FROM pessoa;



