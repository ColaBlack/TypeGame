#include "../libs/httplib.h"

//全局互斥锁对象
std::mutex mutex;

// 玩家1进度
int progress1 = -1;

// 玩家2进度
int progress2 = -1;

// 数据文本
std::string text;

int main() {
	//读取数据文件text.txt
	std::ifstream file("text.txt");

	if (!file.good()) {
		MessageBox(NULL, L"数据文件打开失败！", L"错误", MB_OK);
		return -1;
	}

	std::stringstream ss;
	ss << file.rdbuf();
	text = ss.str();
	file.close();

	httplib::Server svr;
	svr.Post("/user/login", userLogin);
	svr.Post("/data/get", getData);
	svr.Post("/progress/exchange1", exchangeProcess1);
	svr.Post("/progress/exchange2", exchangeProcess2);
	svr.listen("0.0.0.0", 1221);
	return 0;
}

// 登录接口
void userLogin(const httplib::Request& req, httplib::Response& res) {
	std::lock_guard<std::mutex> lock(mutex);

	if (progress1 >= 0 && progress2 >= 0) {
		res.set_content("-1", "text/plain");
		return;
	}
	else {
		res.set_content(progress1 >= 0? "1" : "2", "text/plain");
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