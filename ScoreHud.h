#pragma once
#include "Neon.h"
#include "GameSettings.h"

// ゲーム中、画面右上にスコア(上)と生存時間(下)を描くクラス
// 数値は持たず、描くときにScoreクラスから読む
class ScoreHud
{
public:
	static void Draw();

private:
	// フォントは最初のDrawで1回だけ作る(-1はまだ作っていない)
	static inline int m_fontHandle = -1;
	static const int FONT_SIZE = 40;

	static const int RIGHT_X = GameSettings::SCREEN_WIDTH - 40;	// 文字の右端のX座標(画面の右から40)
	static const int SCORE_Y = 32;					// 「SCORE」の上端のY座標
	static const int TIME_Y = SCORE_Y + 52;			// 「TIME」の上端のY座標(スコアの下)

	static constexpr NeonColor SCORE_COLOR = Neon::CYAN;	// HPバーと同じ色
	static constexpr NeonColor TIME_COLOR = Neon::CYAN;

	static void DrawRightString(int y, const TCHAR* text, NeonColor color);
};
