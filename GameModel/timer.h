#pragma once
#include<functional>

class Timer {
public:
	Timer() = default;
	~Timer() = default;

	// 重置计时器
	void reset() {
		this->passTime = 0;
		this->hasShotted = false;
	}

	// 设置计时器等待时间
	void setWaitTime(int waitTime) {
		this->waitTime = waitTime;
	}

	// 设置计时器到时运行的回调函数
	void setOnFinishCallback(std::function<void()> onFinishCallback) {
		this->onFinishCallback = onFinishCallback;
	}

	// 设置计时器是否只运行一次
	void setOneShot(bool oneShot) {
		this->oneShot = oneShot;
	}

	// 暂停计时器
	void pause() {
		this->hasPaused = true;
	}

	// 开始计时器
	void start() {
		this->hasPaused = false;
	}

	// 更新计时器
	void onUpdate(int deltaTime) {
		if (this->hasPaused) {
			return;
		}
		this->passTime += deltaTime;
		if (this->passTime >= this->waitTime) {
			//如果计时器到时，
			// 并且计时器不是只运行一次，
			// 或者计时器只允许运行一次但还没有被触发过
			// 则在回调函数村存在的情况下运行回调函数
			if (((!this->oneShot||(this->oneShot&&!this->hasShotted)))&&this->onFinishCallback){
				this->onFinishCallback();
		}
			this->hasShotted = true;
			this->passTime = 0;
		}
	}
private:
	//计时器已经运行的时间
	int passTime = 0;
	//计时器等待的时间
	int waitTime = 0;
	//计时器是否暂停
	bool hasPaused = false;
	// 计时器是否被触发
	bool hasShotted = false;
	// 计时器是否只运行一次
	bool oneShot = false;
	// 计时器到时运行的回调函数
	std::function<void()> onFinishCallback;
};