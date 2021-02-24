#include <string>
#include "headers/Server.h"
extern "C" {
#include "headers/mongoose.h"
}


/// <summary>
/// Run server with event handler options
/// </summary>
/// <returns>False if connection to the server failed</returns>
bool Server::runServer()
{
	struct mg_mgr eManager;
	struct mg_connection* connector;

	// Run Mongoose server
	mg_mgr_init(&eManager);

	connector = mg_http_listen(&eManager, address, eHandler, &eManager);

	// Connection failed
	if (connector == NULL) {
		return false;
	}

	while (true) mg_mgr_poll(&eManager, 1000); // Run the server
	mg_mgr_free(&eManager);

	return true;
}

/**
* Standard event handler implementation
*/
void eHandler(struct mg_connection* connector, int ev, void* ev_data, void* fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_serve_opts opts = { "./serverdir", "#.shtml" };
		mg_http_serve_dir(connector, (struct mg_http_message*)ev_data, &opts);
	}
	(void)fn_data;
}
