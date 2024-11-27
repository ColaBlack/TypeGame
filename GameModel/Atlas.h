#pragma once
#include <vector>
#include<graphics.h>

// 图集类
class Atlas {
public:
	Atlas() = default;
	~Atlas() = default;

	// 添加图像到图集
	void loadFromFile(const LPCTSTR pathTemplate, const int numOfImages) {
		images.clear();
		images.resize(numOfImages);
		TCHAR path[MAX_PATH];
		for (int i = 1; i <= numOfImages; i++) {
			wsprintf(path, pathTemplate, i);
			loadimage(&images[i - 1], path);
		}
	}

	// 清空图集
	void clear() {
		images.clear();
	}

	// 获取图集大小
	int getSize() {
		return images.size();
	}

	// 获取指定索引的图像
	IMAGE* getImage(const int index) {
		if (index < 0 || index >= images.size()) {
			return nullptr;
		}
		return &images[index];
	}

	// 添加图像到图集
	void addImage(const IMAGE& img) {
		images.push_back(img);
	}
private:
	std::vector<IMAGE> images;
};