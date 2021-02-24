#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include "WebList.h"
#include "WebPage.h"

#define LOGNAME_DEFAULT "weblist.log"

using namespace std;

/// <summary>
/// Upload Web Pages from the file to the list
/// </summary>
/// <param name="filename">Name of the file</param>
/// <returns>
/// True if uploading successful
/// False if uploading failed
/// </returns>
bool WebList::uploadList(const std::string& filename)
{
	ifstream inputFile(filename);
	string buffer; 

	// Chech if the file is opened
	if (!inputFile.is_open()) {
		return false;
	}

	// Read the configuration line by line
	while (getline(inputFile, buffer)) {
		istringstream bufferInput(buffer);

		WebPage page;
		if (bufferInput >> page) {
			webList.push_back(page);
		}
	}

	return true;
}

void WebList::checkAll()
{
	for (auto &page : webList) {
		auto start = chrono::high_resolution_clock::now(); // Set the timestamp
		bool reqResult = page.request(); // Make a request and save the result
		auto stop = chrono::high_resolution_clock::now(); // Set the timestamp

		bool conResult = page.checkCondition(); // Check the content and save the result

		auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); // Calculate the response time

		// Update response time
		page.setTime(duration.count());

		// Update page status
		if (reqResult && conResult) { 
			page.setStatus("OK");
		}
		else if (reqResult && !conResult) {
			page.setStatus("CONTENT MISSING");
		}
		else {
			page.setStatus("FAILED");
		}
	}
}

/// <summary>
/// Save page information to log file
/// </summary>
void WebList::saveLog() const
{
	ofstream outputFile;
	outputFile.open("weblist.log", std::ios_base::app); // Open file in append mode

	// Print the log line by line in format:
	// DATE TIME URL STATUS RESPONSE_TIME
	for (auto page : webList) {
		// Calculate current time 
		auto currentTime = chrono::system_clock::now();
		time_t time = chrono::system_clock::to_time_t(currentTime);

		outputFile << put_time(gmtime(&time), "%F %X") << " " << page << endl;
	}

	outputFile << endl;
}