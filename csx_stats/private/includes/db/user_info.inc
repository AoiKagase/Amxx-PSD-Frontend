<?php
require_once(__DIR__ . "/_table.inc");
class T_USER_INFO extends T_CORE
{
	function __construct(&$dbh)
	{
		parent::__construct($dbh);

		$this->table = 'user_info';

		$this->key = [
			'auth_id',
		];

		$this->field = [
			'auth_id',
			'name',
			'latest_ip',
			'geoip_code2',
			'online_time',
			'created_at',
			'updated_at',
		];
	}

	function GetNewerList($where = [])
	{
		$result = array();
		$sql = 'SELECT '
			.'	A.auth_id'
			.',	A.name'
			.', A.latest_ip'
			.', A.geoip_code2'
			.',	SEC_TO_TIME(FROM_UNIXTIME(A.online_time) - FROM_UNIXTIME(0)) AS online_time'
			.' FROM user_info AS A'
			.' WHERE created_at >= (SELECT MAX(created_at) FROM user_info AS B WHERE B.auth_id = A.auth_id)'
			.' GROUP BY A.auth_id'
			.' ORDER BY A.auth_id';

		try
		{
			$prp = $this->dbh->prepare($sql);
			$prp->execute();
			$result = $prp->fetchAll(PDO::FETCH_ASSOC);
		}
		catch (PDOException $e)
		{
			echo $e->getMessage() . "\n";
		}
		return $result;

	}

	function GetUser($where = [])
	{
		if (!isset($where['auth_id']))
			return array();

		$result = array();
		$sql = 'SELECT '
			.'	A.auth_id'
			.',	A.name'
			.',	SEC_TO_TIME(A.online_time) AS online_time'
			.' FROM user_info AS A'
			.' WHERE auth_id = :auth_id'
			.' ORDER BY A.auth_id, A.created_at DESC';
		try
		{
			$prp = $this->dbh->prepare($sql);
			$prp->bindValue(':auth_id', $where['auth_id']);
			$prp->execute();
			$result = $prp->fetch(PDO::FETCH_ASSOC);
		}
		catch (PDOException $e)
		{
			echo $e->getMessage() . "\n";
		}
		return $result;

	}


}
