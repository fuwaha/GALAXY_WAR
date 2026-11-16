#include <DxLib.h>
#include "Player.h"
#include "GameScene.h"
#include "GameSettings.h"
#include "DebugDisplay.h"
#include "Score.h"

enum class GameState
{
	Init,//	ゲーム全体の初期化用
	TitleInit,//タイトルの初期化
	TitleDsp,//タイトル表示
	TitleEnd,//タイトルの終了処理
	InGameInit,//インゲームの初期化
	InGameDsp,//インゲームの表示
	InGameEnd,//インゲームの終了処理
	GameOverInit,
	GameOverDsp,
	GameOverEnd,
	End,//　ゲーム全体の終了処理
};

GameState gameState = GameState::Init;

// オブジェクトの生成
GameScene gameScene;

int keyCode = 0;

//以下、ゲーム全体の状態管理
void SetState(GameState state)
{
	gameState = state;
}

GameState GetState()
{
	return gameState;
};

void StateControll()
{


	switch (gameState)
	{
	case GameState::Init:
		Score::LoadHighScoreFile();
		SetState(GameState::TitleInit);
		break;

	case GameState::TitleInit:
		SetState(GameState::TitleDsp);
		break;

	case GameState::TitleDsp:
		gameScene.m_currentScene->Draw();

		if (CheckHitKey(KEY_INPUT_SPACE))
			SetState(GameState::TitleEnd);
		break;

	case GameState::TitleEnd:
		gameScene.ChangeToInGameScene();
		SetState(GameState::InGameInit);
		break;

	case GameState::InGameInit:
		gameScene.m_currentScene->Initialize();
		SetState(GameState::InGameDsp);
		break;

	case GameState::InGameDsp:
		gameScene.m_currentScene->Update();
		gameScene.m_currentScene->Draw();

		if (gameScene.m_currentScene->IsInGameEnd())
			SetState(GameState::InGameEnd);

		break;

	case GameState::InGameEnd:
		Score::UpdateHighScore();
		gameScene.ChangeToGameOverScene();
		SetState(GameState::GameOverInit);
		break;

	case GameState::GameOverInit:
		gameScene.m_currentScene->Initialize();
		SetState(GameState::GameOverDsp);
		break;

	case GameState::GameOverDsp:
		gameScene.m_currentScene->Update();
		gameScene.m_currentScene->Draw();

		if (CheckHitKey(KEY_INPUT_RETURN)) 
		{
			keyCode = KEY_INPUT_RETURN;
			SetState(GameState::GameOverEnd);
		}

		if (CheckHitKey(KEY_INPUT_T))
		{
			keyCode = KEY_INPUT_T;
			SetState(GameState::GameOverEnd);
		}
		break;

	case GameState::GameOverEnd:
		if (keyCode == KEY_INPUT_RETURN) 
		{
			gameScene.ChangeToInGameScene();
			SetState(GameState::InGameInit);
		}

		if (keyCode == KEY_INPUT_T)
		{
			gameScene.ChangeToTitleScene();
			SetState(GameState::TitleInit);
		}
		keyCode = 0;

		break;

	case GameState::End:
		break;
	}

	if (DebugDisplay::IsVisible())
	{
		if (gameState == GameState::TitleDsp)
			DrawFormatString(20, 20, GetColor(255, 255, 0), L"TitleScene");
		if (gameState == GameState::InGameDsp)
			DrawFormatString(20, 20, GetColor(255, 255, 0), L"InGameScene");
		if (gameState == GameState::GameOverDsp)
			DrawFormatString(20, 20, GetColor(255, 255, 0), L"GameOverScene");
	}
}

//メインループ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT, 32);
	ChangeWindowMode(FALSE);	// フルスクリーン
	SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	SetFontSize(32);	// 標準フォントの大きさ(1920×1080用に2倍)

	while (ProcessMessage() == 0 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		LONGLONG frameStartTime = GetNowHiPerformanceCount();	// フレーム開始時刻(マイクロ秒)

		ClearDrawScreen();

		// F1でデバッグ表示の切り替え
		DebugDisplay::Update();

		StateControll();

		ScreenFlip();

		// 1フレーム分の時間が経つまで待つ
		LONGLONG elapsedTime = GetNowHiPerformanceCount() - frameStartTime;
		if (elapsedTime < GameSettings::FRAME_TIME) {
			WaitTimer(static_cast<int>((GameSettings::FRAME_TIME - elapsedTime) / 1000));
		}
	}
	// キー入力を待ってから終了する
	WaitKey();
	DxLib_End();
	return 0;
}
