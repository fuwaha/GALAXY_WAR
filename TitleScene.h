#pragma once
#include <DxLib.h>
#include "Scene.h"
#include "Neon.h"
#include "StarField.h"
class TitleScene :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	// フォントは最初のDrawで1回だけ作る(-1はまだ作っていない)
	static inline int m_titleFontHandle = -1;	// タイトル文字用
	static inline int m_textFontHandle = -1;	// 案内文字用

	StarField m_starField;						// 背景の星空
	float m_starScrollY = 0.0f;					// 星空を流した量
	static constexpr float STAR_SCROLL_SPEED = 1.0f;	// 星空が1フレームに流れる量(実際は層ごとの倍率がかかる)
	static const int BLINK_INTERVAL = 500;		// 「SPACE to start」の点滅間隔(ミリ秒)

	// フォントの大きさ
	static const int TITLE_FONT_SIZE = 144;		// タイトル文字
	static const int TEXT_FONT_SIZE = 48;		// 案内文字

	// 文字の縦位置(画面の高さに対する割合。0=上端、1=下端)
	static constexpr float TITLE_Y_RATE = 0.315f;	// タイトル
	static constexpr float LINE_Y_RATE = 0.49f;		// タイトルの下線
	static constexpr float START_Y_RATE = 0.63f;		// 「SPACE to start」
	static constexpr float GUIDE_Y_RATE = 0.889f;	// 操作説明

	void DrawBackground();
	void DrawCenterString(int y, const TCHAR* text, NeonColor color, int fontHandle);
	static int ToScreenY(float rate);
};