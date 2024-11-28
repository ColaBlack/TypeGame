#pragma once
#include"Atlas.h"
#include"Vector2D.h"
#include"Animation.h"

class Player {
public:

	void onUpdate(double deltaTime) {
		// 如果玩家没有接近目标位置
		if (!this->position.approx(this->positionTarget)) {
			//就让玩家的速度矢量指向目标位置，大小为奔跑速度
			this->velocity = (this->positionTarget - this->position).normalize() * this->speedRun;
		}
		else {
			//到达目标位置，速度归零
			this->velocity = Vector2D(0, 0);
		}

		//如果玩家在当前帧移动的距离大于其和目标位置的距离，说明玩家在当前帧到达目标位置
		if ((this->positionTarget - this->position).length() <= (this->velocity * deltaTime).length()) {
			//更新玩家位置为目标位置
			this->position = this->positionTarget;
		}
		else {
			this->position += this->velocity * deltaTime;
		}

		if (this->velocity.approx(Vector2D(0, 0))) {
			switch (this->facing) {
			case Facing::UP:
				this->currentAnimation = this->atlasIdleUp;
				break;
			case Facing::DOWN:
				this->currentAnimation = this->atlasIdleDown;
				break;
			case Facing::LEFT:
				this->currentAnimation = this->atlasIdleLeft;
				break;
			case Facing::RIGHT:
				this->currentAnimation = this->atlasIdleRight;
				break;
			}
		}
		else {
			switch (this->facing) {
			case Facing::UP:
				this->currentAnimation = this->atlasRunUp;
				break;
			case Facing::DOWN:
				this->currentAnimation = this->atlasRunDown;
				break;
			case Facing::LEFT:
				this->currentAnimation = this->atlasRunLeft;
				break;
			case Facing::RIGHT:
				this->currentAnimation = this->atlasRunRight;
				break;
			}
		}
		if (!this->currentAnimation) {
			return;
		}
		this->currentAnimation->setPosition(this->position);
		this->currentAnimation->onUpdate(deltaTime);
	}

	void onDraw(const Camera& camera) {
		if (!this->currentAnimation) {
			return;
		}
		this->currentAnimation->onDraw(camera);
	}
	// 玩家朝向枚举
	enum class Facing {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Player(Atlas* atlasIdleUp, Atlas* atlasIdleDown, Atlas* atlasIdleLeft, Atlas* atlasIdleRight,
		Atlas* atlasRunUp, Atlas* atlasRunDown, Atlas* atlasRunLeft, Atlas* atlasRunRight) {
		// 初始化加载动画资源
		this->atlasIdleUp->setLoop(true);
		this->atlasIdleUp->setInterval(0.1);
		this->atlasIdleUp->addFrame(atlasIdleUp);

		this->atlasIdleDown->setLoop(true);
		this->atlasIdleDown->setInterval(0.1);
		this->atlasIdleDown->addFrame(atlasIdleDown);

		this->atlasIdleLeft->setLoop(true);
		this->atlasIdleLeft->setInterval(0.1);
		this->atlasIdleLeft->addFrame(atlasIdleLeft);

		this->atlasIdleRight->setLoop(true);
		this->atlasIdleRight->setInterval(0.1);
		this->atlasIdleRight->addFrame(atlasIdleRight);

		this->atlasRunUp->setLoop(true);
		this->atlasRunUp->setInterval(0.1);
		this->atlasRunUp->addFrame(atlasRunUp);

		this->atlasRunDown->setLoop(true);
		this->atlasRunDown->setInterval(0.1);
		this->atlasRunDown->addFrame(atlasRunDown);

		this->atlasRunLeft->setLoop(true);
		this->atlasRunLeft->setInterval(0.1);
		this->atlasRunLeft->addFrame(atlasRunLeft);

		this->atlasRunRight->setLoop(true);
		this->atlasRunRight->setInterval(0.1);
		this->atlasRunRight->addFrame(atlasRunRight);

	}

	~Player() = default;

	//设置玩家位置
	void setPosition(const Vector2D& position) {
		this->position = position;
	}

	//获取玩家位置
	const Vector2D& getPosition() const {
		return this->position;
	}

	//设置玩家目标位置
	void setPositionTarget(const Vector2D& positionTarget) {
		this->positionTarget = positionTarget;
	}
private:
	//玩家奔跑速度
	const double speedRun = 100;

	//玩家位置
	Vector2D position;

	//玩家速度矢量
	Vector2D velocity;

	//玩家目标位置
	Vector2D positionTarget;

	//当前正在播放的动画
	Animation* currentAnimation = nullptr;

	//玩家朝向
	Facing facing = Facing::DOWN;

	//玩家动画
	Animation* atlasIdleUp;
	Animation* atlasIdleDown;
	Animation* atlasIdleLeft;
	Animation* atlasIdleRight;
	Animation* atlasRunUp;
	Animation* atlasRunDown;
	Animation* atlasRunLeft;
	Animation* atlasRunRight;
};