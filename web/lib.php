<?
function readFromDB($limit = null){

	if(is_null($limit))
		$limitStr = '';

	elseif($limit > 0)
		$limitStr = ' LIMIT ' . $limit;

	$db = new PDO('mysql:host=localhost;dbname=arduino', 'arduino', 'arduino');

	$statement = $db->query('SELECT * FROM log ORDER BY id DESC' . $limitStr);

	$result = $statement->fetchAll(PDO::FETCH_ASSOC);

	return $result;
}