#pragma once
#include"vector2d.h"

class Camera {
public:
	Camera() = default;
	~Camera() = default;

	// 重置摄像机位置为(0,0)
	void reset() {
		this->position.x = 0;
		this->position.y = 0;
	}

	void onUpdate(int deltaTime) {
	}

	const Vector2D& getPosition() const {
		return this->position;
	}
private:
	Vector2D position;
};