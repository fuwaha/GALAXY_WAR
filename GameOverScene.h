#pragma once
#include <DxLib.h>
#include "Scene.h"
#include "Neon.h"
#include "StarField.h"
class GameOverScene :
    public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	// フォントは最初のDrawで1回だけ作る(-1はまだ作っていない)
	static inline int m_titleFontHandle = -1;	// 「GAME OVER」用
	static inline int m_textFontHandle = -1;	// 案内文字用

	StarField m_starField;						// 背景の星空
	static const int BACK_TINT_ALPHA = 40;		// 背景をうっすら赤くする幕の濃さ(0~255)

	// フォントの大きさ
	static const int TITLE_FONT_SIZE = 144;		// 「GAME OVER」
	static const int TEXT_FONT_SIZE = 48;		// 案内文字

	// 文字の縦位置(画面の高さに対する割合。0=上端、1=下端)
	static constexpr float TITLE_Y_RATE = 0.315f;		// 「GAME OVER」
	static constexpr float LINE_Y_RATE = 0.49f;			// 「GAME OVER」の下線
	static constexpr float RETRY_Y_RATE = 0.63f;		// 「ENTER : RETRY」
	static constexpr float TITLE_BACK_Y_RATE = 0.713f;	// 「T : TITLE」

	void DrawBackground();
	void DrawCenterString(int y, const TCHAR* text, NeonColor color, int fontHandle);
	static int ToScreenY(float rate);
};

