/**
* The following program is design by Pavel Arefyev
* The task was initially requested by F-Secure
* GitHub: /DedUndead
* GutHub Repo: /DedUndead/WebMonitor
*/

#include <iostream>
#include "WebPage.h"
#include "WebList.h"
#include "Server.h"

#define CHECK_TIME_MIN 10
#define CHECK_TIME_MAX 86400
#define CHECK_TIME_DEFAULT 10
#define ARG_MAX 3 // Maximum number of arguments

using namespace std;


int main(int argc, char* argv[])
{
	// TODO: Command line arguments for filename, seconds
	// TODO: HTTP host
	// TODO: save initial URLs, optimize 
	// TODO: clear logs
	// TODO: conditional compiling
	WebList webList;
	Server httpServer;
	string confFileName;
	int checkingPeriod = CHECK_TIME_DEFAULT; // Default checking period

	httpServer.runServer();

	// Terminate the program & send instructions if no arguments were passed/invalid number of arguments
	if (argc == 1 || argc > ARG_MAX) {
		cout << " Invalid number of arguments passed!" << endl;
		cout << " *First argument - Configuration file." << endl;
		cout << " Second argument - Checking period time (default = 300s)." << endl;
		return 0;
	}
	
	// Save the configuration file name
	confFileName = argv[1];
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
			cout << " Checking period time invalid. Must be a number between 10 - 86400." << endl;
		}
	}

	if (webList.uploadList(confFileName)) {
		while (true) {
			webList.checkAll();
			webList.saveLog();
			Sleep(checkingPeriod * 1000);
		}
	}
	else {
		cout << " Error while trying to open the file. Check the file name." << endl;
	}

	return 0;
}
