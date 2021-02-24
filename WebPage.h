#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

/// <summary>
/// WebPage class handles HTTP request to induvidual pages
/// </summary>
class WebPage
{
	friend std::ostream& operator<<(std::ostream& out, const WebPage& targetPage);
	friend std::istream& operator>>(std::istream& in, WebPage& targetPage);
public:
	// Default constructor
	WebPage(std::string target = "Undef", std::string condition = "Default") : 
		    response("Undef"), content(condition), url(target), status("Undef") {} 
	bool request();
	bool checkCondition() const;
	// Setters 
	void setStatus(const std::string& newStatus) { status = newStatus; } // Setter for changing page status
	void setTime(const int& newTime) { responseTime = newTime; } // Setter for response time
	// Getter in case they are needed / debug purpose
	std::string getResponse() const { return response; } 
	std::string getStatus() const { return status; }
private:
	std::string solveDirectory();
	std::string solveDomain();
	void cutProtocol();
	std::string content;
	std::string response;
	std::string url;
	std::string status;
	int responseTime;
};