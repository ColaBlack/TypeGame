#pragma once
#include"vector2d.h"
#include<vector>

class Path {
public:
	Path(const std::vector<Vector2D>& points) {
		this->pointList = points;

		for (size_t i = 1; i < pointList.size(); i++) {
			double length = (pointList[i] - pointList[i - 1]).length();
			this->lengthList.push_back(length);
			this->length += length;
		}
	}
	~Path() = default;

	Vector2D getPositionByProgress(double progress) const {
		if (progress < 0) {
			return pointList.front();
		}
		if (progress > 1) {
			return pointList.back();
		}

		// 已经行走的距离
		double walkDistance = progress * this->length;

		double currentLength = 0;

		// 遍历路径片段
		for (size_t i = 1; i < pointList.size(); i++) {
			currentLength += lengthList[i - 1];
			// 已经遍历累加的距离大于等于当前走过的距离，则说明当前位置在当前片段上
			if (currentLength >= walkDistance) {
				// 计算当前位置所处的片段的进度百分比
				double partProgress = (walkDistance - (currentLength - lengthList[i - 1])) / lengthList[i - 1];
				return pointList[i - 1] + (pointList[i] - pointList[i - 1]) * partProgress;
			}
		}
		return pointList.back();
	}
private:

	//路径总长度
	double length;

	//路径顶点列表
	std::vector<Vector2D> pointList;

	//路径各个顶点之间的长度列表
	std::vector<double> lengthList;
};