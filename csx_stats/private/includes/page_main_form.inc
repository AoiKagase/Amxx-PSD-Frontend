<?php
require_once(__DIR__ . "/SteamID.inc");
require_once(__DIR__ . "/page_main.inc");

use GuzzleHttp\Client;
use GuzzleHttp\Promise;
use GuzzleHttp\Psr7;

class PageMainForm extends PageMain
{
	protected function calculate_rate(&$dataset, $info = null)
	{
		if (isset($info))
		{
			$dataset['name']		= $info['name'];
			$dataset['latest_ip']	= $info['latest_ip'];
			$dataset['online_time']	= $info['online_time'];
		}
		$dataset['efficiency'] 	= 0;
		$dataset['accuracy']	= 0;
		$dataset['accuracyHS']	= 0;
		$dataset['kdrate']		= 0;
		$dataset['csx_elo']		= 0;

        if (($dataset['csx_kills'] + $dataset['csx_deaths']) > 0)
			$dataset['efficiency'] 	= round((floatval($dataset['csx_kills']) / floatval($dataset['csx_kills'] + $dataset['csx_deaths'])) * 100.0, 2, PHP_ROUND_HALF_DOWN);

		if ($dataset['csx_shots'] > 0)
		{
			$dataset['accuracy']	= round((floatval($dataset['csx_hits'])  / floatval($dataset['csx_shots']))  * 100.0, 2, PHP_ROUND_HALF_DOWN);
			$dataset['accuracyHS']	= round((floatval($dataset['csx_hs'])    / floatval($dataset['csx_shots']))  * 100.0, 2, PHP_ROUND_HALF_DOWN);
		}

		if ($dataset['csx_deaths'] > 0)
			$dataset['kdrate']		= round((floatval($dataset['csx_kills']) / floatval($dataset['csx_deaths'])), 2, PHP_ROUND_HALF_DOWN);
		else
			$dataset['kdrate']		= $dataset['csx_kills'];
	}

	protected function get_user_steam_link($auth_ids = [])
	{
		$client = new Client();
		$promises = [];
		// Need Your Steam API key
		$WebAPIKey = STEAM_API_KEY;
//		$WebAPIKey = '';
		$Parameters =
		[
			'key' => $WebAPIKey,
			'steamids' => '',
		];

		$i = 0;
		foreach($auth_ids as $str_auth_ids)
		{
			$steam_ids = '';
			$ids = explode(',', $str_auth_ids);
			foreach ($ids as $auth_id) {
				if (isset($auth_id) && $auth_id !== '') {
					$s = new SteamID($auth_id);
					$steam_ids .= $s->ConvertToUInt64() . ',';
				}
			}
			$Parameters['steamids'] = $steam_ids;
			$api_url = 'https://api.steampowered.com/ISteamUser/GetPlayerSummaries/v2/?'. http_build_query($Parameters);
			try
			{
				$promises[$i++] = $client->getAsync($api_url);

			} catch(\GuzzleHttp\Exception\ClientException $e)
			{
				echo $e->getHandlerContext()['errno'];
			}
		}

		$result  = [];

		try {

			$results = Promise\Utils::unwrap($promises);
			foreach($results as $response)
			{
				if ($response->getStatusCode() == 200)
				{
					$json = json_decode($response->getBody(), true);
					if(isset($json['response']['players']))
						$result = array_merge($result, $json['response']['players']);
				}
			}
		} catch (\GuzzleHttp\Exception\ClientException $e) {
//			echo Psr7\Message::toString($e->getRequest());
			echo Psr7\Message::toString($e->getResponse());
		}
		$result = array_column($result, null, 'steamid');
        return $result;
	}
}