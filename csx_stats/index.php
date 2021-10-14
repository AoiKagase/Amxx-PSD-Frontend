<?php
require_once("includes/page_main_form.inc");
require_once("includes/db/user_info.inc");
require_once("includes/db/user_wstats.inc");

class Index extends PageMainForm
{
	private $ELO_IMAGE = [
		//Rank 		  		XP/Lvl
		["Silver I"		,	0		,"ranks/silver_1.png"], // Lvl 0
		["Silver I"		,	40		,"ranks/silver_1.png"], // Lvl 1
		["Silver I"		,	60		,"ranks/silver_1.png"], // Lvl 2
		["Silver II"	,	80		,"ranks/silver_2.png"], // Lvl 3
		["Silver II"	, 	100		,"ranks/silver_2.png"], // Lvl 4
		["Silver II"	,	120		,"ranks/silver_2.png"], // Lvl 5
		["Silver III"	,	140		,"ranks/silver_3.png"], // Lvl 6
		["Silver III"	,	160		,"ranks/silver_3.png"], // Lvl 7
		["Silver III"	,	180		,"ranks/silver_3.png"], // Lvl 8
		["Silver IV"	,	200		,"ranks/silver_4.png"], // Lvl 9
		["Silver IV"	,	220		,"ranks/silver_4.png"], // Lvl 10
		["Silver IV"	,	240		,"ranks/silver_4.png"], // Lvl 11
		["Silver V"		,	260		,"ranks/silver_5.png"], // Lvl 12
		["Silver V"		,	280		,"ranks/silver_5.png"], // Lvl 13
		["Silver V"		,	300		,"ranks/silver_5.png"], // Lvl 14
		["Elite Silver"	,	320		,"ranks/silver_e.png"], // Lvl 15
		["Elite Silver"	,	340		,"ranks/silver_e.png"], // Lvl 16
		["Elite Silver"	,	350		,"ranks/silver_e.png"], // Lvl 17
		["Gold I"		,	500		,"ranks/gold_1.png"], // Lvl 18
		["Gold I"		,	550		,"ranks/gold_1.png"], // Lvl 19
		["Gold I"		,	600		,"ranks/gold_1.png"], // Lvl 20
		["Gold I"		,	650		,"ranks/gold_1.png"], // Lvl 21
		["Gold I"		,	700		,"ranks/gold_1.png"], // Lvl 22
		["Gold II"		,	800		,"ranks/gold_2.png"], // Lvl 23
		["Gold II"		,	900		,"ranks/gold_2.png"], // Lvl 24
		["Gold II"		,	1000	,"ranks/gold_2.png"], // Lvl 25
		["Gold II"		,	1100	,"ranks/gold_2.png"], // Lvl 26
		["Gold II"		,	1200	,"ranks/gold_2.png"], // Lvl 27
		["Gold III"		,	1400	,"ranks/gold_3.png"], // Lvl 28
		["Gold III"		,	1500	,"ranks/gold_3.png"], // Lvl 29
		["Gold III"		,	1600	,"ranks/gold_3.png"], // Lvl 30
		["Gold IV"		,	1800	,"ranks/gold_4.png"], // Lvl 31
		["Gold IV"		,	2000	,"ranks/gold_4.png"], // Lvl 32
		["Gold IV"		,	2200	,"ranks/gold_4.png"], // Lvl 33
		["AK I"			,	2600	,"ranks/ak_1.png"], // Lvl 34
		["AK I"			,	2900	,"ranks/ak_1.png"], // Lvl 35
		["AK I"			,	3200	,"ranks/ak_1.png"], // Lvl 36
		["AK II"		,	3500	,"ranks/ak_2.png"], // Lvl 37
		["AK II"		,	3800	,"ranks/ak_2.png"], // Lvl 38
		["AK II"		,	4100	,"ranks/ak_2.png"], // Lvl 39
		["AK Crusade"	,	4500	,"ranks/ak_c.png"], // Lvl 40
		["AK Crusade"	,	5000	,"ranks/ak_c.png"], // Lvl 41
		["AK Crusade"	,	5500	,"ranks/ak_c.png"], // Lvl 42
		["Sheriff"		,	6500	,"ranks/sheriff.png"], // Lvl 43
		["Sheriff"		,	7000	,"ranks/sheriff.png"], // Lvl 44
		["Sheriff"		,	7500	,"ranks/sheriff.png"], // Lvl 45
		["Eagle I"		,	8500	,"ranks/eagle_1.png"], // Lvl 46
		["Eagle I"		,	9000	,"ranks/eagle_1.png"], // Lvl 47
		["Eagle I"		,	9500	,"ranks/eagle_1.png"], // Lvl 48
		["Eagle II"		,	10000	,"ranks/eagle_2.png"], // Lvl 49
		["Eagle II"		,	11000	,"ranks/eagle_2.png"], // Lvl 50
		["Eagle II"		,	12000	,"ranks/eagle_2.png"], // Lvl 51
		["Supreme"		,	15000	,"ranks/supreme.png"], // Lvl 52
		["Supreme"		,	20000	,"ranks/supreme.png"], // Lvl 53
		["Supreme"		,	25000	,"ranks/supreme.png"], // Lvl 54
		["Supreme"		,	30000	,"ranks/supreme.png"], // Lvl 55
		["Supreme"		,	35000	,"ranks/supreme.png"], // Lvl 56
		["Global Elite"	,	50000	,"ranks/global_e.png"]  // Lvl 57
	];

	public function __construct()
	{
		parent::__construct();
	}

	protected function select()
	{
		$data = $this->get_ranking_top();
		echo $this->twig->render('index.tpl', ['ranking' => $data]);
	}

	protected function get_ranking_top()
	{
		$info		= new T_USER_INFO($this->dbh);
		$info_rec	= $info->GetNewerList();

		$stats		= new T_USER_WSTATS($this->dbh);
		$stats_rec 	= $stats->GetTopRanker();

		$info_array = array_column($info_rec, null, "auth_id");

		$steam_data = $this->get_steam_user_info($stats_rec);
		
		for($i = 0; $i < count($stats_rec); $i++)
		{
			if ($stats_rec[$i]['auth_id'] !== 'BOT')
			{
				$s = new SteamID($stats_rec[$i]['auth_id']);
				$auth_id = $s->ConvertToUInt64();
				if (isset($steam_data[$auth_id]))
				{
					$stats_rec[$i]['steam_data'] = $steam_data[$auth_id]; 
					try
					{
						if (isset($info_array[$stats_rec[$i]['auth_id']]['latest_ip']))
						{
							$country_rec 		   = $this->geoip->city($info_array[$stats_rec[$i]['auth_id']]['latest_ip']);
							$stats_rec[$i]['country'] = strtolower($country_rec->country->isoCode);
						}
					} catch(Exception $err)
					{
					}
				}

				$stats_rec[$i]['csx_rank'] = $i + 1;
				$this->calculate_rate($stats_rec[$i], $info_array[$stats_rec[$i]['auth_id']]);


				// Get WpnStats;
				$auth_id = $stats_rec[$i]['auth_id'];
				$stats_rec[$i]['csx_xp'] = 0;
				if (isset($info))
				{
					$wstats_sc 	= $this->get_user_wstats($auth_id);
					if ($wstats_sc)
					{
						$wstats_sc 	= $this->get_user_wstats($auth_id);
						$stats_rec[$i]['csx_xp'] += ($wstats_sc[0]['csx_knife'] * 4);
						$stats_rec[$i]['csx_xp'] += ($wstats_sc[0]['csx_hegrenade'] * 5);
						$stats_rec[$i]['csx_xp'] += ($wstats_sc[0]['csx_hs'] * 3);
						$stats_rec[$i]['csx_xp'] += ($wstats_sc[0]['csx_kills'] * 2);	
					}	
					$wstats_sc = null;
				}

				$iLevel = 0;
				while ($stats_rec[$i]['csx_xp'] > $this->ELO_IMAGE[$iLevel][1])
				{
					if ($iLevel < 57)
						$iLevel++;
				}
				$stats_rec[$i]['csx_elo_name'] = $this->ELO_IMAGE[$iLevel][0];
				$stats_rec[$i]['csx_elo'] = $this->ELO_IMAGE[$iLevel][2];
			}
		}
		return $stats_rec;
	}

	private function get_steam_user_info($records)
	{
		$auth_ids 	= $this->make_steamid_list($records);

		$steam_data = [];
		foreach($auth_ids as $auth_records)
		{
			$steam_data += $this->get_user_steam_link($auth_records);
		}
		return $steam_data;
	}

	private function make_steamid_list($records)
	{
		$result = [];
		$i = 0;
		$n = 0;
		foreach($records as $player)
		{
			if (!isset($result[$n]))
				$result[$n] = '';

			if ($player['auth_id'] !== 'BOT')
			{
				$result[$n] .= $player['auth_id'].',';
				$i++;
			}

			if ($i >= 50) 
			{
				$i = 0; $n++;
			}
		}
		return $result;
	}

	private function get_user_wstats($auth_id)
	{
		$stats		= new T_USER_WSTATS($this->dbh);
		$where = [
			'server_id' => $this->server_id,
			'auth_id'	=> $auth_id,
		];

		return $stats->GetEloRankForUser($where);
	}	
}
$index = new Index();
$index->main();
