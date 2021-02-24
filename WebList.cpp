#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include "headers/WebList.h"
#include "headers/WebPage.h"

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

	for (auto page : webList) {

		outputFile << getTime() << " " << page << endl;
	}

	outputFile << endl;
}

void WebList::updateHTML() const
{
	ofstream outputFile;
	outputFile.open("serverdir/index.html");

	// Write to HTML file
	outputFile << getHeadHTML();
	for (auto page : webList) {
		outputFile << "<pre p>" << getTime() << " " << page.getFormatHTML() << endl;
	}
	outputFile << getTailHTML();
}

/**
* Calculate current time
*/
string WebList::getTime() const
{
	ostringstream timeStream;

	auto currentTime = chrono::system_clock::now();
	time_t time = chrono::system_clock::to_time_t(currentTime);
	timeStream << put_time(gmtime(&time), "%F %X");

	return timeStream.str();
}

/**
* Obtain HEAD of the HTML file
*/
string WebList::getHeadHTML() const
{
	ostringstream temp;

	temp << "<!DOCTYPE html>" << endl;
	temp << "<html lang=\"en - US\">" << endl;
	temp << "<head>" << endl;
	temp << "	<meta charset=\"utf - 8\">" << endl;
	temp << "	<title>WEB MONITOR</title>" << endl;
	temp << "</head>" << endl;
	temp << "<body>" << endl;
	temp << "<main>" << endl;

	return temp.str();
}

/**
* Obtain the rest of the HTML page
*/
string WebList::getTailHTML() const
{
	ostringstream temp;

	temp << "</main>" << endl;
	temp << "<hr>" << endl;
	temp << "<p> Web Monitor by Pavel Arefyev </p>" << endl;
	temp << "</html>";

	return temp.str();
}