# Player Stats in DB Front End Web Page
Player Stats in DB Front End Web Page

Using Twig Template.

Nginx Settings.
```
    location /csx_stats/ {
        alias [YOUR DIRECTORY]/csx_stats/public/;
        index index.php;

        location  ~* \.(php|tpl|inc)$ {
            fastcgi_intercept_errors on;
            fastcgi_pass        unix:/var/run/php-fpm/php-fpm.sock;
            fastcgi_index       index.php;
            fastcgi_param       SCRIPT_FILENAME     $request_filename;
            include             fastcgi_params;
        }
        break;
    }
```

Create View
```
CREATE VIEW `total_stats_view` AS select `A1`.`server_id` AS `server_id`,`A1`.`auth_id` AS `auth_id`,`A1`.`csx_score` AS `csx_score`,`A1`.`csx_kills` AS `csx_kills`,`A1`.`csx_tks` AS `csx_tks`,`A1`.`csx_deaths` AS `csx_deaths`,`A1`.`csx_hits` AS `csx_hits`,`A1`.`csx_dmg` AS `csx_dmg`,`A1`.`csx_shots` AS `csx_shots`,`A1`.`csx_hs` AS `csx_hs`,`A1`.`h_head` AS `h_head`,`A1`.`h_chest` AS `h_chest`,`A1`.`h_stomach` AS `h_stomach`,`A1`.`h_larm` AS `h_larm`,`A1`.`h_rarm` AS `h_rarm`,`A1`.`h_lleg` AS `h_lleg`,`A1`.`h_rleg` AS `h_rleg`,`B`.`name` AS `name`,`B`.`online_time` AS `online_time`,`B`.`geoip_code2` AS `geoip_code2` from ((select `A`.`server_id` AS `server_id`,`A`.`auth_id` AS `auth_id`,sum(`A`.`csx_kills`) - sum(`A`.`csx_deaths`) AS `csx_score`,sum(`A`.`csx_kills`) AS `csx_kills`,sum(`A`.`csx_tks`) AS `csx_tks`,sum(`A`.`csx_deaths`) AS `csx_deaths`,sum(`A`.`csx_hits`) AS `csx_hits`,sum(`A`.`csx_dmg`) AS `csx_dmg`,sum(`A`.`csx_shots`) AS `csx_shots`,sum(`A`.`csx_hs`) AS `csx_hs`,sum(`A`.`h_head`) AS `h_head`,sum(`A`.`h_chest`) AS `h_chest`,sum(`A`.`h_stomach`) AS `h_stomach`,sum(`A`.`h_larm`) AS `h_larm`,sum(`A`.`h_rarm`) AS `h_rarm`,sum(`A`.`h_lleg`) AS `h_lleg`,sum(`A`.`h_rleg`) AS `h_rleg` from `amxx_psd`.`user_wstats` `A` group by `A`.`server_id`,`A`.`auth_id` order by sum(`A`.`csx_kills`) desc,sum(`A`.`csx_hits`) desc) `A1` join (select `U`.`auth_id` AS `auth_id`,`U`.`name` AS `name`,`U`.`latest_ip` AS `latest_ip`,`U`.`geoip_code2` AS `geoip_code2`,sec_to_time(from_unixtime(`U`.`online_time`) - from_unixtime(0)) AS `online_time` from `amxx_psd`.`user_info` `U` where `U`.`created_at` >= (select max(`U1`.`created_at`) from `amxx_psd`.`user_info` `U1` where `U1`.`auth_id` = `U`.`auth_id` group by `U1`.`auth_id`) group by `U`.`auth_id` order by `U`.`auth_id`) `B` on(`B`.`auth_id` = `A1`.`auth_id`)) group by `A1`.`server_id`,`A1`.`auth_id` order by `A1`.`csx_score` desc,`A1`.`csx_hits` desc ;
```
