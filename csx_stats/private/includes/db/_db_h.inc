<?php
require_once(__DIR__ . "/../_config.inc");

class DBHandler extends PDO
{
	public function __construct($dsn, $user = null, $pass = null, array $options = null)
	{
		parent::__construct($dsn, $user, $pass, $options);
	}
	
	static function CreateConnection()
	{
		$con = null;
		try
		{
			$dsn = sprintf("mysql:host=%s;dbname=%s", DB_HOST, DB_NAME);
			$con = new DBHandler($dsn, DB_USER, DB_PASS);
		} catch (PDOException $e)
		{
			echo 'DATABASE BROKEN...';//$e->getMessage();
		}
		return $con;
	}

	static function Close(&$con)
	{
		$con = null;
	}
}
