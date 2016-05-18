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

	public void selecionar(s s) {
		String sql = 'SELECT * FROM Users';
		Statement statement = conn.createStatement();
		ResultSet result = statement.executeQuery(sql);
		int count = 0;
		while (result.next()) {
			String name = result.getString(2);
			String fullname = result.getString('fullname');
		}
		String output = 'User #Teste: Teste1 - Teste2';
		System.out.println(String.format(output, ++count, name, fullname));
	}

	public void autalizar(S s) {
		String sql = 'UPDATE s SET column1=?, column2=? WHERE username=?';
		PreparedStatement statement = conn.preparedStatement(sql);
		statement.setString(1, 'Teste 1');
		statement.setString(2, 'Teste 2');
		int rowsInserted = statement.executeUpdate();
		if (rowsInserted > 0) {
			System.out.println('An existing user was updated successfully!');
		}
	}

	public void excluir(User user) {
		String sql = 'DELETE FROM User WHERE username=?';
		PreparedStatement statement = conn.preparedStatement(sql);
		statement.setString(1, user);
		int rowsInserted = statement.executeUpdate();
		if (rowsInserted > 0) {
			System.out.println('An existing user was deleted successfully!');
		}
	}