<?php
require_once(__DIR__ . "/_table.inc");
class T_USER_STATS extends T_CORE
{
	function __construct(&$dbh)
	{
		parent::__construct($dbh);

		$this->table = 'user_stats';

		$this->key = [
			'server_id',
			'date',
			'auth_id',
		];

		$this->field = [
			'server_id',
			'date',
			'round',
			'auth_id',
			'csx_rank',
			'csx_score',
			'csx_kills',
			'csx_tks',
			'csx_deaths',
			'csx_hits',
			'csx_dmg',
			'csx_shots',
			'csx_hs',
			'h_head',
			'h_chest',
			'h_stomach',
			'h_larm',
			'h_rarm',
			'h_lleg',
			'h_rleg',
			'created_at',
			'updated_at',
		];
	}
}