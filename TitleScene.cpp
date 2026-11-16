#include <DxLib.h>
#include "TitleScene.h"
#include "GameSettings.h"
#include "DebugDisplay.h"

void TitleScene::Initialize()
{}

void TitleScene::Update()
{}

void TitleScene::Draw()
{
	// フォントは最初に描くときに作る
	// (TitleSceneはDxLib_Initより前に作られるので、コンストラクタでは作れない)
	if (m_titleFontHandle == -1)
		m_titleFontHandle = CreateFontToHandle(NULL, TITLE_FONT_SIZE, 6, DX_FONTTYPE_ANTIALIASING_8X8);
	if (m_textFontHandle == -1)
		m_textFontHandle = CreateFontToHandle(NULL, TEXT_FONT_SIZE, 3, DX_FONTTYPE_ANTIALIASING_8X8);

	DrawBackground();

	// タイトル(仮)と下線
	const TCHAR* title = L"GALAXY WAR";
	int titleWidth = GetDrawStringWidthToHandle(title, lstrlen(title), m_titleFontHandle);
	DrawCenterString(ToScreenY(TITLE_Y_RATE), title, Neon::CYAN, m_titleFontHandle);

	float lineLeft = (GameSettings::SCREEN_WIDTH - titleWidth) / 2.0f;
	float lineY = static_cast<float>(ToScreenY(LINE_Y_RATE));
	Neon::DrawGlowLine(lineLeft, lineY, lineLeft + titleWidth, lineY, Neon::MAGENTA, 2.0f);

	// 開始の案内(点滅)
	bool isBlinkOn = (GetNowCount() / BLINK_INTERVAL) % 2 == 0;
	if (isBlinkOn)
		DrawCenterString(ToScreenY(START_Y_RATE), L"SPACE to start", Neon::MAGENTA, m_textFontHandle);

	// 操作説明
	const TCHAR* guide = L"WASD : MOVE    MOUSE : AIM    L-CLICK : SHOOT    ESC : QUIT";
	int guideWidth = GetDrawStringWidth(guide, lstrlen(guide));
	DrawString((GameSettings::SCREEN_WIDTH - guideWidth) / 2, ToScreenY(GUIDE_Y_RATE), guide, Neon::ToColor(Neon::TEXT_DIM));
}

// 背景(暗い床に、下へゆっくり流れる星空)
void TitleScene::DrawBackground()
{
	DrawBox(0, 0, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT, Neon::ToColor(Neon::FLOOR), TRUE);

	// 上方向にずらしていくと、星は下へ流れて見える
	m_starScrollY -= STAR_SCROLL_SPEED;
	m_starField.Draw(0.0f, m_starScrollY, true);
}

// 画面の横中央に光る文字を描く
void TitleScene::DrawCenterString(int y, const TCHAR* text, NeonColor color, int fontHandle)
{
	int textWidth = GetDrawStringWidthToHandle(text, lstrlen(text), fontHandle);
	Neon::DrawGlowString((GameSettings::SCREEN_WIDTH - textWidth) / 2, y, text, color, fontHandle);
}

// 画面の高さに対する割合から、画面上のY座標を出す
int TitleScene::ToScreenY(float rate)
{
	return static_cast<int>(GameSettings::SCREEN_HEIGHT * rate);
}