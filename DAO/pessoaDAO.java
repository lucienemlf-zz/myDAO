public class PessoaDAO {

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

	public Pessoa selecionar(String cpf) {
		String sql = 'SELECT * FROM Pessoa WHERE cpf = ?';
		Pessoa pessoa = new Pessoa();
		PreparedStatement statement = conn.preparedStatement(sql);
		statement.setString(1, cpf);
		ResultSet result = statement.executeQuery(sql);
		while (result.next()) {
			pessoa.setNome(result.getString(1));
			pessoa.setCpf(result.getString(2));
			pessoa.setFone(result.getString(3));
		}
		return pessoa;
	}

	public void atualizar(Pessoa pessoa) {
			String sql = 'UPDATE pessoa SET' +
			'nome=?' +
			'fone=?' +
			'WHERE cpf=?';
			PreparedStatement statement = conn.preparedStatement(sql);
			statement.setInt(1, pessoa.getNome());
			statement.setInt(2, pessoa.getFone());
			statement.setString(3, pessoa.getCpf());
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println('An existing user was updated successfully!');
			}
		}

	public void excluir(Pessoa pessoa) {
			String sql = 'DELETE FROM pessoa WHERE cpf=?';
			PreparedStatement statement = conn.preparedStatement(sql);
			statement.setString(1, pessoa.getCpf());
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println('An existing user was deleted successfully!');
			}
		}
}