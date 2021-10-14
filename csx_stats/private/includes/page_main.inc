<?php
require_once(__DIR__ . "/../vendor/autoload.php");
require_once(__DIR__ . "/_config.inc");
require_once(__DIR__ . "/db/_db_h.inc");
// use GeoIp2\Database\Reader;

class PageMain
{
	protected $loader;
	protected $twig;
	protected $dbh;
	protected $server_id;
	// protected $geoip;

	public function __construct()
	{
		$this->dbh			= DBHandler::CreateConnection();
		$this->server_id	= 1;
		$this->loader		= new \Twig\Loader\FilesystemLoader(__DIR__ . "/../". TWIG_TEMPLATE_DIR);
		$this->twig			= new \Twig\Environment($this->loader, ['cache' => __DIR__ . "/../". TWIG_COMPILED_DIR, 'auto_reload' => true]);
		// $this->geoip 		= new Reader(GEOIP_DATABASE);
	}

	public function main()
	{
		$this->select();

		$this->end();
	}

	protected function select()
	{
	}

	protected function end()
	{
		DBHandler::Close($dbh);
	}
}
