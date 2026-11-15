#pragma once
#include "Neon.h"
#include "GameSettings.h"

// HPバー(画面に固定して表示する)を描くクラス
// HPの数値は持たず、描くときに今のHPと最大HPを受け取るだけ
class HpBar
{
public:
	static void Draw(int hp, int maxHp);

private:
	static const int BAR_X = 40;		// バーの左上のX座標(画面座標)
	static const int BAR_Y = GameSettings::SCREEN_HEIGHT - 80;	// バーの左上のY座標(画面の下から80)
	static const int BAR_WIDTH = 480;	// バーの横幅
	static const int BAR_HEIGHT = 28;	// バーの高さ
	static const int FILL_ALPHA = 160;	// 中身の濃さ(0~255)
	static const int EMPTY_ALPHA = 40;	// 減った部分の濃さ(同じ色をうすく)(0~255)
	static constexpr float FRAME_THICKNESS = 2.0f;	// 枠の線の太さ
	static constexpr NeonColor BAR_COLOR = Neon::CYAN;	// プレイヤーと同じ色
};
