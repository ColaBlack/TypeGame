#pragma once
#include "../libs/httplib.h"

extern std::string text;
extern int progress1;
extern int progress2;
extern std::mutex mutex;
// 登录接口
void userLogin(const httplib::Request& req, httplib::Response& res) {
	std::lock_guard<std::mutex> lock(mutex);

	if (progress1 >= 0 && progress2 >= 0) {
		res.set_content("-1", "text/plain");
		return;
	}
	else {
		res.set_content(progress1 >= 0 ? "1" : "2", "text/plain");
	}
}

//获取数据文本接口
void getData(const httplib::Request& req, httplib::Response& res) {
	res.set_content(text, "text/plain");
}

// 玩家1交换进度接口
void exchangeProcess1(const httplib::Request& req, httplib::Response& res) {
	std::lock_guard<std::mutex> lock(mutex);

	int progress = std::stoi(req.body);
	if (progress < 0 || progress > 100) {
		res.set_content("-500", "text/plain");
		return;
	}

	progress1 = progress;
	res.set_content(std::to_string(progress2), "text/plain");
}

// 玩家2交换进度接口
void exchangeProcess2(const httplib::Request& req, httplib::Response& res) {
	std::lock_guard<std::mutex> lock(mutex);

	int progress = std::stoi(req.body);
	if (progress < 0 || progress > 100) {
		res.set_content("-500", "text/plain");
		return;
	}

	progress2 = progress;
	res.set_content(std::to_string(progress1), "text/plain");
}