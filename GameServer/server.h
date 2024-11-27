#pragma once
#include "controller.h"

void startServer() {
	httplib::Server svr;
	svr.Post("/user/login", userLogin);
	svr.Post("/data/get", getData);
	svr.Post("/progress/exchange1", exchangeProcess1);
	svr.Post("/progress/exchange2", exchangeProcess2);
	svr.listen("0.0.0.0", 1221);
}