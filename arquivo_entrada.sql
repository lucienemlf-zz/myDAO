CREATE TABLE pessoa (
nome INT NOT NULL CHECK,
cpf VARCHAR,
fone INT
);

CREATE TABLE carro (
placa VARCHAR,
montadora VARCHAR,
chassi INT
);


SELECT * FROM carro;
SELECT nome FROM pessoa;
SELECT * FROM montadora;

