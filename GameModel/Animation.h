#pragma once
#include "Atlas.h"
#include"ImgUtils.h"
#include<functional>

class Animation {
public:
	Animation() = default;
	~Animation() = default;

	// 设置动画贴图集
	void setAtlas(Atlas* atlas) {
		reset();
		this->atlas = atlas;
	}

	// 播放动画
	void onUpdate(int deltaTime) {
		this->timer += deltaTime;
		if (this->timer >= this->frameInterval) {
			this->timer = 0;
			this->frameIndex++;
			if (this->frameIndex >= this->atlas->getSize() - 1) {
				this->frameIndex = this->loop ? 0 : (atlas->getSize() - 1);
				if (!this->loop && this->onDie) {
					this->onDie();
				}
			}
		}
	}

	// 绘制动画
	void onDraw(int x, int y) {
		putImageAlpha(this->atlas->getImage(frameIndex), x, y);
	}

	// 设置死亡回调函数
	void setOnDie(std::function<void()> onDie) {
		this->onDie = onDie;
	}
	// 重置动画播放进度
	void reset() {
		timer = 0;
		frameIndex = 0;
	}

	// 设置动画是否循环播放
	void setLoop(bool loop) {
		this->loop = loop;
	}

	// 设置帧间隔
	void setInterval(int interval) {
		this->frameInterval = interval;
	}

	// 设置当前帧索引
	int getFrameIndex() {
		return this->frameIndex;
	}

	// 获取当前播放的动画帧
	IMAGE* getCurrentFrame() {
		return atlas->getImage(frameIndex);
	}

	// 判断动画是否结束播放
	bool hasFinished() {
		return this->loop ? false : (frameIndex >= atlas->getSize() - 1);
	}
private:
	Atlas* atlas = nullptr;
	// 计时器
	int timer = 0;
	//帧间隔
	int frameInterval = 0;
	//当前帧索引
	int frameIndex = 0;
	//是否需要循环播放
	bool loop = true;
	//游戏对象死亡的回调函数
	std::function<void()> onDie = nullptr;
public:
};