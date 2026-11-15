#pragma once
#include "TitleScene.h"
#include "InGameScene.h"
#include "GameOverScene.h"
#include <memory>

class GameScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<Scene> m_currentScene;

	void ChangeToTitleScene();
	void ChangeToInGameScene();
	void ChangeToGameOverScene();

private:
};