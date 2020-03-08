QPang Essence Emulator set-up instructions

Pre-requisites: 
  - Visual Studio 2017
  - CMake [https://cmake.org/download]
  - vcpkg [https://github.com/microsoft/vcpkg]
  - MySQL connector [https://dev.mysql.com/downloads/c-api/] (6.1 x86 version)
  - MySQL server [https://dev.mysql.com/downloads/mysql/]
  - PHP ^7.2 [https://www.php.net/downloads.php]
  - Composer [https://getcomposer.org/download/]
  - QPang Essence API [https://github.com/Deluze/qpang-essence-api]
  
^ The server currently only works on Windows. Linux will be supported in the future (needs some rework for that). However, you can still build the server on Linux if you want to contribute.


I recommend installing something like XAMPP, which is basically a PHP & MySQL container for what we currently need. 
I don't recommend installing MySQL server since it will be a service that's on 24/7. XAMPP resolves this for you.


### API SETUP ###

1. Login to your MySQL server. And create a database, preferably under the name 'qpang'
2. Open the root of the QPang Essence API in your terminal.
3. Run the following command: `cp .env.example .env`
4. Open the newly created `.env` file with your favorite text editor.
5. Fill in the following environment variables:
  - DB_HOST (the host where your database is located at, in this case 127.0.0.1)
  - DB_PORT (leave this at 3306, unless configured to be different)
  - DB_DATABASE (your database name, in step 1 we called this 'qpang')
  - DB_USERNAME (username for your mysql server, most likely this will be 'root')
  - DB_PASSWORD (password for your mysql server, you have chosen this on the setup of your MySQL server, if you don't know this is probably empty)
  - APP_DEBUG (let this stay on 'true' for debugging purposes, if you ever want to use this API in a live environment.. PUT THIS TO FALSE)
6. When your credentials are all correctly filled in, go back to your terminal, make sure you added the php executable in your PATH variables. (you can check this by typing `php -v` in your terminal)
7. Run the command `composer install`, or `php composer.phar install` depending on the composer installation you did.
8. Run the command `php artisan migrate`, this will setup all the database tables you need for the game.
9. Run the command `php artisan db:seed`, this will create a test user that is important for later use.
10. If you want, you can import the additional database dumps found in the `database` directory in the source of the emulator.
11. Finally, after all this is done. Run the API by running the following command: `php artisan serve`. This will open up a server, most likely on port 8000. We need this server later on.

### VCPKG SETUP ###

After you have installed VCPKG its time to set-up the toolchain. All you have to do is:

1. Open your terminal
2. Run the command: `setx VCPKG_ROOT the/path/to/your/vcpkg/root`
3. Run the command: `vcpkg install boost spdlog curlpp` (WINDOWS USERS ONLY)

That's all :)

### SERVER SETUP ###

You can generate a Visual Studio 2017 solution with our cmake project setup.
Open up the root folder of the essence emulator with your terminal.

Run the following commands:
  - `mkdir build`
  - `cd build`
  - `cmake ..`

When all is fine, cmake should tell you the build files have been written to the build directory.
When it's not fine, it will tell you that there have been errors printed to a log. 
When you fix these errors, please remove the 'build' folder and start all over. If you don't remove the build folder, you will run the cached configuration of cmake again and you don't want that.

After the solution has been build. You will find an `.sln` file in the build directory. Open the solution.

Now, the only thing you need to do is open the `/shared/net/database.hpp` file and edit the database credentials on the top.

In your solution explorer, open your solution settings and select all the projects you want to build on debug, you want to choose for:
  - authserver
  - lobbyserver
  - sqaureserver
  - roomserver
  
these are the 4 processes needed to run the server. excluding the running backend php server.
if you have setup all the project dependencies using default settings, everything should work now.

When you're done. We didn't work on post CMake events yet. 

!important!

- Copy libs/libmysql to the build folder of the executables. Otherwise you'll get an according error message.

Only thing is that internal server communication is kind of bad right now, so you need to make sure all 4 servers start up at the same time.
You can do this by launching the 4 projects in visual studio, or create a shell script that opens the 4 servers. That's up to you :)

If you need any server modifications, you can make them in the 'settings' table in the database. (Hopefully this will become a dedicated config file in the server root in the future)

If everything works and the servers are listening for connections. Make sure you have installed our client and game. Make modifications to the QPangID.ini file in the QPang directory to set the host the game wants to connect to.

To get back to the test user that has been created using the `php artisan db:seed` command. The credentials of this account are: 
  - username: Admin
  - password: password
  
The current generated shop will only have 1 item in the `items` table. If you want the shop to work, please remove the current existing item and import the shop dump in the 'database' folder.
Restart your server and game, and voila :)
