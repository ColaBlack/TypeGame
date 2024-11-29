#pragma once
#include "Atlas.h"
#include"ImgUtils.h"
#include<functional>
#include"timer.h"

class Animation {
public:
	Animation() {
		this->timer.setOneShot(false);
		this->timer.setOnFinishCallback([&]() {
			this->frameIndex++;
			if (this->frameIndex >= this->frames.size()) {
				this->frameIndex = loop ? 0 : (int)frames.size() - 1;
				if (!loop && this->onFinished) {
					this->onFinished();
				}
			}
			});
	};

	~Animation() = default;

	// 重置动画
	void reset() {
		this->frameIndex = 0;
		this->timer.reset();
	}

	void setPosition(const Vector2D& position) {
		this->position = position;
	}

	void setLoop(bool loop) {
		this->loop = loop;
	}

	// 设置动画帧间隔
	void setInterval(float interval) {
		this->timer.setWaitTime(interval);
	}

	// 设置动画播放结束的回调函数
	void setOnFinished(const std::function<void()>& onFinished) {
		this->onFinished = onFinished;
	}

	// 添加动画帧，带裁切功能
	void addFrame(IMAGE* image, int num) {
		int w = image->getwidth();
		int h = image->getheight();
		int frameWidth = w / num;

		for (int i = 0; i < num; i++) {
			Rect rect;
			rect.x = i * frameWidth;
			rect.y = 0;
			rect.w = frameWidth;
			rect.h = h;

			this->frames.emplace_back(image, rect);
		}
	}

	// 从图集中添加动画帧，不带裁切功能
	void addFrame(Atlas* atlas) {
		for (int i = 0; i < atlas->getSize(); i++) {
			IMAGE* image = atlas->getImage(i);
			int w = image->getwidth();
			int h = image->getheight();

			Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = w;
			rect.h = h;

			this->frames.emplace_back(image, rect);
		}
	}

	void onUpdate(double deltaTime) {
		timer.onUpdate(deltaTime);
	}

	void onDraw(const Camera& camera) {
		const Frame& frame = this->frames[this->frameIndex];

		Rect rect = frame.rect;
		rect.x = (int)this->position.x - frame.rect.w / 2;
		rect.y = (int)this->position.y - frame.rect.h / 2;
		rect.w = frame.rect.w;
		rect.h = frame.rect.h;

		putImageAlphaCam(camera, frame.image, &rect);
	}
private:

	// 动画帧结构体
	struct Frame {
		Rect rect;
		IMAGE* image = nullptr;

		Frame() = default;
		Frame(IMAGE* image, const  Rect& rect) : rect(rect), image(image) {}

		~Frame() = default;
	};

	// 动画帧集合
	std::vector<Frame> frames= {};

	// 计时器
	Timer timer= Timer();

	// 动画位置
	Vector2D position= Vector2D();

	//当前帧索引
	int frameIndex = 0;

	//是否需要循环播放
	bool loop = true;

	//动画播放结束的回调函数
	std::function<void()> onFinished = nullptr;
public:
};