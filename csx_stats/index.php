<?php
require_once("includes/page_main.inc");
require_once("includes/db/user_info.inc");
require_once("includes/db/total_stats.inc");
class Index extends PageMain
{
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

		$stats		= new T_TOTAL_STATS($this->dbh);
		$stats_rec 	= $stats->GetTopRanker();

		$info_array = array_column($info_rec, null, "auth_id");
		$result 	= $this->calculate_rate($stats_rec, $info_array);

		$auth_ids = "";
		foreach($result as $player)
		{
			if ($player['auth_id'] !== 'BOT')
				$auth_ids .= $player['auth_id'].',';
		}
		
		$steam_data = $this->get_user_steam_link($auth_ids);
		
		for($i = 0; $i < count($result); $i++)
		{
			if ($result[$i]['auth_id'] !== 'BOT')
			{
				$s = new SteamID($result[$i]['auth_id']);
				$auth_id = $s->ConvertToUInt64();
				if (isset($steam_data[$auth_id]))
				{
					$result[$i]['steam_data'] = $steam_data[$auth_id]; 
					try
					{
						$country_rec 		   = $this->geoip->city($result[$i]['latest_ip']);
						$result[$i]['country'] = strtolower($country_rec->country->isoCode);				
					} catch(Exception $err)
					{

					}
				}
			}
		}
		return $result;
	}
}
$index = new Index();
$index->main();