#include <DxLib.h>
#include "GameScene.h"
#include <memory>

GameScene::GameScene()
{
	m_currentScene = std::make_unique<TitleScene>();
}

GameScene::~GameScene()
{
	m_currentScene.reset();
}

void GameScene::ChangeToTitleScene()
{
	m_currentScene = std::make_unique<TitleScene>();
}

void GameScene::ChangeToInGameScene()
{
	m_currentScene = std::make_unique<InGameScene>();
}

void GameScene::ChangeToGameOverScene() 
{
	m_currentScene = std::make_unique<GameOverScene>();
}