#pragma once
#include"vector2d.h"
#include"timer.h"

class Camera {
public:
	////抖动的构造函数
	//Camera() {
	//	this->shakeTimer.setOneShot(true);
	//	this->shakeTimer.setOnFinishCallback([this]() {
	//		this->isShaking = false;
	//		reset();
	//		});
	//}
	Camera() = default;
	Camera(Vector2D size) {
		this->size = size;
	}
	~Camera() = default;

	// 重置摄像机位置为(0,0)
	void reset() {
		this->position.x = 0;
		this->position.y = 0;
	}

	void onUpdate(int deltaTime) {
		this->shakeTimer.onUpdate(deltaTime);
		if (this->isShaking) {
			this->position.x = (rand() % 100 - 50) / 50 * this->shakeAmount;
			this->position.y = (rand() % 100 - 50) / 50 * this->shakeAmount;
		}
		//const Vector2D speed = { -0.35,0 };
		//this->position += speed * deltaTime;
	}

	//抖动摄像机
	void shake(double amount, int shakeTime) {
		this->shakeAmount = amount;
		this->isShaking = true;
		this->shakeTimer.setWaitTime(shakeTime);
		this->shakeTimer.start();
	}

	// 使摄像机看向目标位置
	void lookAt(const Vector2D& target) {
		this->position = target - this->size / 2.0;
	}

	// 设置摄像机大小
	void setSize(const Vector2D& size) {
		this->size = size;
	}

	//获取摄像机大小
	const Vector2D& getSize() const {
		return this->size;
	}

	// 设置摄像机位置
	void setPosition(const Vector2D& position) {
		this->position = position;
	}

	//获取摄像机位置
	const Vector2D& getPosition() const {
		return this->position;
	}
private:
	// 摄像机位置
	Vector2D position;

	// 摄像机大小
	Vector2D size;

	// 摄像机抖动计时器
	Timer shakeTimer;

	// 摄像机抖动幅度
	double shakeAmount = 0;

	// 是否正在抖动
	bool isShaking = false;
};