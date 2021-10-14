<?php
require_once("vendor/autoload.php");
require_once("includes/_config.inc");
require_once("includes/db/_db_h.inc");
use GeoIp2\Database\Reader;

class PageMain
{
	protected $loader;
	protected $twig;
	protected $dbh;
	protected $server_id;
	protected $geoip;

	public function __construct()
	{
		$this->dbh			= DBHandler::CreateConnection();
		$this->server_id	= 1;
		$this->loader		= new \Twig\Loader\FilesystemLoader(TWIG_TEMPLATE_DIR);
		$this->twig			= new \Twig\Environment($this->loader, ['cache' => TWIG_COMPILED_DIR, 'auto_reload' => true]);
		$this->geoip 		= new Reader(GEOIP_DATABASE);
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
