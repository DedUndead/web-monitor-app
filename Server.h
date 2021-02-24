#pragma once

#include <string>
extern "C" {
	#include "mongoose.h"
}
void eHandler(struct mg_connection* connector, int ev, void* ev_data, void* fn_data);

/// <summary>
/// HTTP server implementation with the use of mongoose library.
/// Library source: https://github.com/cesanta/mongoose
/// </summary>
class Server {
public:
	Server(const char *target = "http://localhost:8000") : address(target) {}
	bool runServer();
private:
	const char *address;
};

/**
* Function to start HTTP server
*/
bool Server::runServer()
{
	struct mg_mgr eManager;
	struct mg_connection *connector;

	// Run Mongoose server
	mg_mgr_init(&eManager);

	connector = mg_http_listen(&eManager, address, eHandler, &eManager);

	// Connection failed
	if (connector == NULL) {
		return false;
	}

	while (true) mg_mgr_poll(&eManager, 1000); // Run the server
}

void eHandler(struct mg_connection* connector, int ev, void* ev_data, void* fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_serve_opts opts = { "./serverdir", "#.shtml" };
		mg_http_serve_dir(connector, (struct mg_http_message*)ev_data, &opts);
	}
	(void)fn_data;
}
