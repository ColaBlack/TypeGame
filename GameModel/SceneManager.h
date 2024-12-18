#pragma once
#include"GameSceneEnums.h"
#include"Scene.h"
#include"MenuScene.h"
#include"GameScene.h"

extern Scene* menuScene;
extern Scene* selectorScene;
extern Scene* gameScene;
extern Scene* overScene;

// 游戏场景管理器
class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	// currentScene的setter
	void SetCurrentScene(Scene* scene) {
		currentScene = scene;
		currentScene->onEnter();
	}

	// 切换场景
	void changeScene(const SceneEnums SceneEnum) {
		if (currentScene) {
			currentScene->onExit();
		}
		switch (SceneEnum) {
		case SceneEnums::MENU:
			currentScene = menuScene;
			break;
		case SceneEnums::SELECTOR:
			currentScene = selectorScene;
			break;
		case SceneEnums::GAME:
			currentScene = gameScene;
			break;
		case SceneEnums::OVER:
			currentScene = overScene;
			break;
		default:
			break;
		}
		currentScene->onEnter();
	}

	void onUpdate(const int deltaTime) {
		if (currentScene) {
			currentScene->onUpdate(deltaTime);
		}
	}

	void onDraw(const Camera& camera) {
		if (currentScene) {
			currentScene->onDraw(camera);
		}
	}

	void onEvent(const ExMessage& msg) {
		if (currentScene) {
			currentScene->onEvent(msg);
		}
	}

private:
	Scene* currentScene = nullptr;
};