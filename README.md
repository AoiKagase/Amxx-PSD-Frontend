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