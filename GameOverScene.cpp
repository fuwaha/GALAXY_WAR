#include <DxLib.h>
#include "GameOverScene.h"
#include "GameSettings.h"
#include "DebugDisplay.h"
#include "Score.h"
#include <cwchar>

void GameOverScene::Initialize() 
{
	// 撃破点から表示を始めて、生存時間ボーナスをあとから足していく
	m_displayScore = Score::GetScore();
	m_restBonus = Score::GetTimeBonus();
	m_countDelayTimer = COUNT_DELAY;

	// COUNT_FRAMESで足し終わる量(最低1)
	m_addPerFrame = (m_restBonus + COUNT_FRAMES - 1) / COUNT_FRAMES;
	if (m_addPerFrame < 1)
		m_addPerFrame = 1;
}

void GameOverScene::Update() 
{
	// 少し待ってから加算を始める
	if (m_countDelayTimer > 0)
	{
		m_countDelayTimer--;
		return;
	}

	// ボーナスを少しずつスコアに移す
	if (m_restBonus > 0)
	{
		int addAmount = (m_restBonus < m_addPerFrame) ? m_restBonus : m_addPerFrame;
		m_displayScore += addAmount;
		m_restBonus -= addAmount;
	}
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

	// スコアと生存時間
	DrawScore();

	// 操作の案内
	DrawCenterString(ToScreenY(RETRY_Y_RATE), L"ENTER : RETRY", Neon::CYAN, m_textFontHandle);
	DrawCenterString(ToScreenY(TITLE_BACK_Y_RATE), L"T : TITLE", Neon::CYAN, m_textFontHandle);
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

// ハイスコア・スコア・生存時間(加算中は生存時間の右に残りのボーナス、加算が終わって新記録ならスコアの右に「NEW RECORD!」を出す)
void GameOverScene::DrawScore()
{
	TCHAR text[64];

	// ハイスコア(InGameEndで更新済みなので、新記録なら今回のスコアと同じ値になる)
	swprintf_s(text, L"HIGH SCORE %06d", Score::GetHighScore());
	DrawCenterString(ToScreenY(HIGH_SCORE_Y_RATE), text, HIGH_SCORE_COLOR, m_textFontHandle);

	swprintf_s(text, L"SCORE %06d", m_displayScore);
	int scoreY = ToScreenY(SCORE_Y_RATE);
	DrawCenterString(scoreY, text, SCORE_COLOR, m_textFontHandle);

	// 加算が終わってから「NEW RECORD!」を出す
	bool isCountFinished = (m_countDelayTimer <= 0 && m_restBonus <= 0);
	if (isCountFinished && Score::IsNewRecord())
		DrawRightOf(scoreY, text, L"NEW RECORD!", NEW_RECORD_COLOR);

	int seconds = Score::GetSurviveSeconds();
	swprintf_s(text, L"TIME %02d:%02d", seconds / 60, seconds % 60);
	int timeY = ToScreenY(TIME_Y_RATE);
	DrawCenterString(timeY, text, SCORE_COLOR, m_textFontHandle);

	if (m_restBonus > 0)
	{
		// 「TIME 01:23」の右どなりに「+830」を出す(TIMEの位置はずらさない)
		TCHAR bonusText[32];
		swprintf_s(bonusText, L"+%d", m_restBonus);
		DrawRightOf(timeY, text, bonusText, BONUS_COLOR);
	}
}

// 中央に描いたcenterTextの右どなりにtextを描く(centerTextの位置はずらさない)
void GameOverScene::DrawRightOf(int y, const TCHAR* centerText, const TCHAR* text, NeonColor color)
{
	int centerWidth = GetDrawStringWidthToHandle(centerText, lstrlen(centerText), m_textFontHandle);
	int x = (GameSettings::SCREEN_WIDTH + centerWidth) / 2 + BONUS_SPACE;
	Neon::DrawGlowString(x, y, text, color, m_textFontHandle);
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