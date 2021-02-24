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