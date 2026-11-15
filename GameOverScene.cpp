#include <DxLib.h>
#include "GameOverScene.h"
#include "GameSettings.h"
#include "DebugDisplay.h"

void GameOverScene::Initialize() 
{

}

void GameOverScene::Update() 
{

}

void GameOverScene::Draw() 
{
	// フォントは最初に描くときに作る(TitleSceneと同じ作り)
	if (m_titleFontHandle == -1)
		m_titleFontHandle = CreateFontToHandle(NULL, TITLE_FONT_SIZE, 6, DX_FONTTYPE_ANTIALIASING_8X8);
	if (m_textFontHandle == -1)
		m_textFontHandle = CreateFontToHandle(NULL, TEXT_FONT_SIZE, 3, DX_FONTTYPE_ANTIALIASING_8X8);

	DrawBackground();

	// 「GAME OVER」と下線
	const TCHAR* title = L"GAME OVER";
	int titleWidth = GetDrawStringWidthToHandle(title, lstrlen(title), m_titleFontHandle);
	DrawCenterString(ToScreenY(TITLE_Y_RATE), title, Neon::RED, m_titleFontHandle);

	float lineLeft = (GameSettings::SCREEN_WIDTH - titleWidth) / 2.0f;
	float lineY = static_cast<float>(ToScreenY(LINE_Y_RATE));
	Neon::DrawGlowLine(lineLeft, lineY, lineLeft + titleWidth, lineY, Neon::MAGENTA, 2.0f);

	// 操作の案内
	DrawCenterString(ToScreenY(RETRY_Y_RATE), L"ENTER : RETRY", Neon::CYAN, m_textFontHandle);
	DrawCenterString(ToScreenY(TITLE_BACK_Y_RATE), L"T : TITLE", Neon::CYAN, m_textFontHandle);

	if (DebugDisplay::IsVisible())
		DrawFormatString(20, 20, GetColor(255, 255, 0), L"GameOverScene");
}

// 背景(暗い床に止まった星空+うっすら赤い幕)
void GameOverScene::DrawBackground()
{
	DrawBox(0, 0, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT, Neon::ToColor(Neon::FLOOR), TRUE);

	// 星空(流さない・瞬きも止める)
	m_starField.Draw(0.0f, 0.0f, false);

	// 全体をうっすら赤くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BACK_TINT_ALPHA);
	DrawBox(0, 0, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT, Neon::ToColor(Neon::RED), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 画面の横中央に光る文字を描く
void GameOverScene::DrawCenterString(int y, const TCHAR* text, NeonColor color, int fontHandle)
{
	int textWidth = GetDrawStringWidthToHandle(text, lstrlen(text), fontHandle);
	Neon::DrawGlowString((GameSettings::SCREEN_WIDTH - textWidth) / 2, y, text, color, fontHandle);
}

// 画面の高さに対する割合から、画面上のY座標を出す
int GameOverScene::ToScreenY(float rate)
{
	return static_cast<int>(GameSettings::SCREEN_HEIGHT * rate);
}