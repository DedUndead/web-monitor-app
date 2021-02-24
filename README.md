# WebMonitor
Console application for monitoring HTTP webpages made by Pavel Arefyev.<br>
The program is done **entirely** in **C++**. However, GitHub sees it as in C, because there is C-library source code included in the project.


# User Interface


### Main algorithm

1. Read the command line arguments
2. Start HTTP sever on http://localhost:8000/
3. Upload the configuration
4. Start making requests, update logs and HTML page on the server


### Web Monitor page

Web Monitor can be accessed on http://localhost:8000/ by default. It is dynamically-updated HTML page, that includes time of the last checking sequence, URL, page status and response time.

![Web Monitor](/images/server.PNG)


### Log File

Logs are saved into "weblist.log" file. It includes time of the last checking sequence, URL, page status and response time.<br>
Each checking sequence is separated by one line.

![Log File](/images/log.PNG)


### Configuration File

Configuration file should be written in the following format:

> URL;Content condition<br>
> http://example.com/;Hello World!

Testing configuration file can be found in the repository under name **testdata.cfg**

![Configuration file](/images/datainput.png)


# Implementation Details

All details can be found in the code comments. The article below shortly describes the main design solutions used in this project.


### HTTP Request Implementation

Requested pages interfaces are implemented with **WebPage** and **WebList** classes.<br><br>
WebPage provides functionality to make the request, using **ASIO library** of [BOOST package](https://www.boost.org/), as well as parse URL and check if the requested content is present.<br> Instances are updated using setters and getters.<br><br>
WebList stores WebPage objects. It can save all the objects to log file, html page, as well as send requests to each of the pages.<br><br>
Classes are related with the association principle.

### Server Implementation 

Server is implemented using [Mongoose C-based](https://github.com/cesanta/mongoose) library. The library is included in the source.<br>
Server is hosted on http://localhost:8000/ by default.<br>
Server interface is represented by **Server** class. It is run in the background thread of the main process.

### Command Line Argument Handling

The program must be executed as following from the command line:

> ./program.cpp CONF_FILE_ARGUMENT CHECKING_TIME

The checking time is 30 by default. Range of the checking time is [30;86400] in seconds.<br>
The default configuration file is set to testdata.cfg.

# Usage Details

In order to use the source code, Boost library must be installed to your IDE. [Installation guide](https://www.youtube.com/watch?v=5afpq2TkOHc&t=419s&ab_channel=ThomasKim) (Taken from Thomas Kin educational YouTube channel).<br>
The path must not include non-ASCII characters.

# References and additional materials

Mongoose C-based library: https://github.com/cesanta/mongoose<br>
Mongoose HTTP-server C-example: https://github.com/cesanta/mongoose/tree/master/examples/http-server<br>
Boost Extension Website: https://www.boost.org/
ASIO Networking Tutorial: https://www.youtube.com/watch?v=2hNdkYInj4g&ab_channel=javidx9
