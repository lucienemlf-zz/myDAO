public class CarroDAO {

	public void inserir(s s) {
			String sql = 'INSERT INTO s (s, s) VALUE (?, ?)';
			PreparedStatement statement = conn.preparedStatement(sql);
			statement.setString(1, 'Teste 1');
			statement.setString(2, 'Teste 2');
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println('A new user was inserted successfully!');
			}
		}

	public Carro selecionar(int chassi) {
		String sql = 'SELECT * FROM Carro WHERE chassi = ?';
		Carro carro = new Carro();
		PreparedStatement statement = conn.preparedStatement(sql);
		statement.setInt(1, chassi);
		ResultSet result = statement.executeQuery(sql);
		while (result.next()) {
			carro.setPlaca(result.getString(1));
			carro.setMontadora(result.getString(2));
			carro.setChassi(result.getString(3));
		}
		return carro;
	}

	public void atualizar(Carro carro) {
			String sql = 'UPDATE carro SET' +
			'placa=?' +
			'montadora=?' +
			'WHERE chassi=?';
			PreparedStatement statement = conn.preparedStatement(sql);
			statement.setString(1, carro.getPlaca());
			statement.setString(2, carro.getMontadora());
			statement.setInt(3, carro.getChassi());
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println('An existing user was updated successfully!');
			}
		}

	public void excluir(Carro carro) {
			String sql = 'DELETE FROM carro WHERE chassi=?';
			PreparedStatement statement = conn.preparedStatement(sql);
			statement.setInt(1, carro.getChassi());
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println('An existing user was deleted successfully!');
			}
		}
}