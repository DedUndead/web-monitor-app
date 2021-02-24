#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>
#include <iomanip>
#include "WebPage.h"

#define HTTP_PORT "80"

using namespace std;
namespace asio = boost::asio;
namespace http = boost::beast::http;

/// <summary>
/// Function makes a request to HTTP server.
/// Reference used: https://www.boost.org/doc/libs/1_70_0/libs/beast/doc/html/beast/quick_start/http_client.html
/// </summary>
/// <returns>
/// The result of the request if the connection successful
///	Error string if the connection failed
/// </returns>
bool WebPage::request()
{
	asio::io_context context; // Asio I/O space
	asio::ip::tcp::resolver resolver(context); // DNS resolver object
	asio::ip::tcp::socket socket(context); // Networking socket object

	cutProtocol();

	string domain = solveDomain();
	try {
		asio::connect(socket, resolver.resolve(domain, HTTP_PORT)); // Establish connection with the target
	}
	catch (exception& e) {
		return false; // Connection failed return
	}

	// Form HTTP request
	string dir = solveDirectory();
	http::request<http::string_body> req(http::verb::get, dir, 11); // Make a request to the certain page
	req.set(http::field::host, domain);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	// Send request
	http::write(socket, req);

	boost::beast::flat_buffer buffer; // Create buffer
	http::response<http::dynamic_body> res;
	http::read(socket, buffer, res); // Read response to the buffer
	response = boost::beast::buffers_to_string(res.body().data()); // Translate buffer to string

	socket.shutdown(asio::ip::tcp::socket::shutdown_both); // Shutdown the connection

	return true; // Request succesful return
}

/**
* Parse domain from the URL
*/
string WebPage::solveDomain()
{
	if (url.find("/") == string::npos) {
		return url;
	}
	else {
		return url.substr(0, url.find("/"));
	}
}

/**
* Parse page of the URL
*/
string WebPage::solveDirectory()
{
	if (url.find("/") == string::npos) {
		return "/";
	}
	else {
		return url.substr(url.find("/"));
	}
}

/**
* Cut the protocol from the url if present
*/
void WebPage::cutProtocol()
{
	if (url.find("//") != std::string::npos) {
		url = url.substr(url.find("//") + 2);
	}
}

/// <summary>
/// Check if the page content meets the requirments 
/// </summary>
/// <returns> 
/// True if content was found on the page
/// False if not
/// </returns>
bool WebPage::checkCondition() const
{
	if (response.find(content) == string::npos) {
		return false;
	}
	else {
		return true;
	}
}

/**
* Overload for writing page information to log
*/
ostream& operator<<(ostream& out, const WebPage& targetPage)
{
	out << setw(70) << left << targetPage.url 
		<< setw(15) << targetPage.status 
		<< setw(6) << right << targetPage.responseTime << "ms";
	return out;
}


/**
* Overload for reading configuration from the file 
*/
istream& operator>>(istream& in, WebPage& targetPage)
{
	// Check if URL format is correct
	if (!getline(in, targetPage.url, ';')) {
		in.setstate(ios_base::failbit);
	}

	// Check is content requirment format is correct
	if (!getline(in, targetPage.content)) {
		in.setstate(ios_base::failbit);
	}

	return in;
}