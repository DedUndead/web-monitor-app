/**
* The following program is design by Pavel Arefyev
* The task was initially requested by F-Secure
* GitHub: /DedUndead
* GutHub Repo: /DedUndead/WebMonitor
*/

#include <iostream>
#include <thread>
#include <chrono>
#include "headers/WebPage.h"
#include "headers/WebList.h"
#include "headers/Server.h"

#define DEFAULT_CFG "testdata.cfg"
#define CHECK_TIME_MIN 30
#define CHECK_TIME_MAX 86400
#define CHECK_TIME_DEFAULT 30
#define ARG_MAX 3 // Maximum number of arguments
#define SERVER_ADDRESS "http://0.0.0.0:8000"

using namespace std;


int main(int argc, char* argv[])
{
	// TODO: optimize 
	// TODO: clear logs
	WebList webList;
	string confFileName;
	int checkingPeriod = CHECK_TIME_DEFAULT; // Default checking period

	// Terminate the program & send instructions if invalid number of arguments
	if (argc > ARG_MAX) {
		cout << " Invalid number of arguments passed!" << endl;
		cout << " *First argument - Configuration file." << endl;
		cout << " Second argument - Checking period time (default = 300s)." << endl;
		return 0;
	}
	
	// Save the configuration file name
	if (argc == 1) {
		confFileName = DEFAULT_CFG;
	}
	else {
		confFileName = argv[1];
	}
	cout << " Uploading configuration from " << confFileName << "..." << endl;
	
	// Saving the checking period time process if present
	if (argc == ARG_MAX) {
		// Check validity
		try {
			int checkTimeTemp = stoi(argv[2]);
			if (checkTimeTemp > CHECK_TIME_MIN || checkTimeTemp < CHECK_TIME_MAX) {
				checkingPeriod = checkTimeTemp; // Save the checking period time
			}
			else {
				throw " Error. Invalid time period.";
			}
		}
		catch (...) {
			cout << " Checking period time invalid. Must be a number between 30 - 86400." << endl;
		}
	}

	thread serverThread(&Server::runServer, Server(SERVER_ADDRESS)); // Run the server in the background thread

	// Main checking loop
	if (webList.uploadList(confFileName)) {
		while (true) {
			webList.checkAll();
			webList.saveLog();
			webList.updateHTML();

			this_thread::sleep_for(chrono::seconds(checkingPeriod)); // Hard-coded delay
		}
	}
	else {
		cout << " Error while trying to open the file. Check the file name." << endl;
	}

	serverThread.detach(); // Terminate server thread 

	return 0;
}
