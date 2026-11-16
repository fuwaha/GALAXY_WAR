#include <DxLib.h>
#include <cwchar>
#include "ScoreHud.h"
#include "Score.h"

void ScoreHud::Draw()
{
	if (m_fontHandle == -1)
		m_fontHandle = CreateFontToHandle(NULL, FONT_SIZE, 3, DX_FONTTYPE_ANTIALIASING_8X8);

	TCHAR text[64];

	// スコア(6桁ゼロ埋め)
	swprintf_s(text, L"SCORE %06d", Score::GetScore());
	DrawRightString(SCORE_Y, text, SCORE_COLOR);

	// 生存時間(分:秒)
	int seconds = Score::GetSurviveSeconds();
	swprintf_s(text, L"TIME %02d:%02d", seconds / 60, seconds % 60);
	DrawRightString(TIME_Y, text, TIME_COLOR);
}

// 右端をRIGHT_Xにそろえて光る文字を描く
void ScoreHud::DrawRightString(int y, const TCHAR* text, NeonColor color)
{
	int textWidth = GetDrawStringWidthToHandle(text, lstrlen(text), m_fontHandle);
	Neon::DrawGlowString(RIGHT_X - textWidth, y, text, color, m_fontHandle);
}
