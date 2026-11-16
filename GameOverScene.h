#pragma once
#include <DxLib.h>
#include "Scene.h"
#include "Neon.h"
#include "StarField.h"
#include "GameSettings.h"
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
	static constexpr float RETRY_Y_RATE = 0.70f;		// 「ENTER : RETRY」
	static constexpr float TITLE_BACK_Y_RATE = 0.783f;	// 「T : TITLE」
	static constexpr float HIGH_SCORE_Y_RATE = 0.515f;	// 「HIGH SCORE」(下線のすぐ下)
	static constexpr float SCORE_Y_RATE = 0.565f;		// 「SCORE」
	static constexpr float TIME_Y_RATE = 0.615f;		// 「TIME」

	// スコアの加算アニメ(生存時間ボーナスを少しずつスコアに足していく)
	int m_displayScore = 0;		// 表示中のスコア
	int m_restBonus = 0;		// まだ足していない生存時間ボーナス
	int m_addPerFrame = 1;		// 1フレームに足す量
	int m_countDelayTimer = 0;	// 加算を始めるまでの残りフレーム
	static const int COUNT_DELAY = GameSettings::FPS / 2;			// 画面が出てから加算を始めるまで(0.5秒)
	static const int COUNT_FRAMES = GameSettings::FPS * 3 / 2;		// ボーナスを足し終えるまでの時間(1.5秒、ボーナスが少ないと早く終わる)
	static constexpr NeonColor SCORE_COLOR = Neon::CYAN;			// 「SCORE」「TIME」の色
	static constexpr NeonColor BONUS_COLOR = Neon::YELLOW;			// まだ足していないボーナス「+830」の色
	static const int BONUS_SPACE = 24;								// 「TIME 01:23」と「+830」、「SCORE」と「NEW RECORD!」の間隔
	static constexpr NeonColor HIGH_SCORE_COLOR = Neon::TEXT_DIM;	// 「HIGH SCORE」の色(今回のスコアより目立たせない)
	static constexpr NeonColor NEW_RECORD_COLOR = Neon::YELLOW;		// 「NEW RECORD!」の色

	void DrawBackground();
	void DrawScore();
	void DrawRightOf(int y, const TCHAR* centerText, const TCHAR* text, NeonColor color);
	void DrawCenterString(int y, const TCHAR* text, NeonColor color, int fontHandle);
	static int ToScreenY(float rate);
};

