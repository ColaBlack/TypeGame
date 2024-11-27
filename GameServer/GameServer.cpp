#include"server.h"

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

	startServer();
	return 0;
}