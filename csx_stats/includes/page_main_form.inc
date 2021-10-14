<?php
require_once("includes/SteamID.inc");
require_once("includes/page_main.inc");

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

	protected function get_user_steam_link($auth_ids = '')
	{
		$ids = explode(',', $auth_ids);
		$auth_ids = '';
		foreach($ids as $auth_id)
		{
			if (isset($auth_id) && $auth_id !== '')
			{
				$s = new SteamID($auth_id);
				$auth_ids .= $s->ConvertToUInt64().',';
			}
		}

		// Need Your Steam API key
		$WebAPIKey = STEAM_API_KEY;

		$Parameters =
		[
			'key' => $WebAPIKey,
			'steamids' => $auth_ids
		];
	
		$api_url = 'https://api.steampowered.com/ISteamUser/GetPlayerSummaries/v2/?' . http_build_query( $Parameters );
		$json = $this->getApiDataCurl($api_url);
	
		if(isset($json['response']['players']))
			return array_column($json['response']['players'], null, 'steamid');

        return array();
	}

    private function getApiDataCurl($url)
    {
        $option = [
            CURLOPT_RETURNTRANSFER => true, //文字列として返す
            CURLOPT_TIMEOUT        => 10, // タイムアウト時間
        ];

        $ch = curl_init($url);
        curl_setopt_array($ch, $option);

        $json    = curl_exec($ch);
        $info    = curl_getinfo($ch);
        $errorNo = curl_errno($ch);

        // OK以外はエラーなので空白配列を返す
        if ($errorNo !== CURLE_OK) {
            // 詳しくエラーハンドリングしたい場合はerrorNoで確認
            // タイムアウトの場合はCURLE_OPERATION_TIMEDOUT
            var_dump($errorNo);
            return [];
        }

        // 200以外のステータスコードは失敗とみなし空配列を返す
        if ($info['http_code'] !== 200) {
            var_dump($info['http_code']);
            return [];
        }

        // 文字列から変換
        $jsonArray = json_decode($json, true);

        return $jsonArray;
    }
}