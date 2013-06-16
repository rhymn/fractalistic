<?

	$db = new PDO('mysql:host=localhost;dbname=arduino', 'arduino', 'arduino');

	$statement = $db->query('SELECT * FROM log ORDER BY id DESC');

	$result = $statement->fetchAll(PDO::FETCH_ASSOC);
