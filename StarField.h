#pragma once
#include <vector>
#include "Neon.h"

// 星空の背景
// 星を遠い・中くらい・近いの3層に分けて、近い層ほど大きくずらす(視差スクロール)
// 星は画面1枚分の範囲に並べて、はみ出した分は反対側から出てくるようにループさせる
class StarField
{
public:
	// scrollX, scrollY : 背景をずらす量(ゲーム中はカメラの位置、タイトルは流した量)
	// isTwinkleOn : 星を瞬かせるか(falseなら全部止まって見える)
	void Draw(float scrollX, float scrollY, bool isTwinkleOn);

private:
	struct Star
	{
		float x;			// 画面1枚分の中での位置
		float y;
		int layer;			// 何番目の層か(FAR_LAYER / MIDDLE_LAYER / NEAR_LAYER)
		NeonColor color;
		bool isTwinkle;		// 瞬く星か
		int twinkleOffset;	// 瞬きのタイミングをずらす量(ミリ秒)
	};

	std::vector<Star> m_stars;
	bool m_isInitialized = false;

	// 層の番号
	static const int FAR_LAYER = 0;
	static const int MIDDLE_LAYER = 1;
	static const int NEAR_LAYER = 2;
	static const int LAYER_COUNT = 3;

	// 層ごとの設定(遠い・中・近いの順)
	static constexpr int STAR_COUNT[LAYER_COUNT] = { 320, 160, 60 };				// 星の数(画面1枚あたり)
	static constexpr float LAYER_SCROLL_RATE[LAYER_COUNT] = { 0.1f, 0.25f, 0.5f };	// ずらす量の倍率(大きいほど速く流れる)
	static constexpr float STAR_RADIUS[LAYER_COUNT] = { 0.0f, 0.9f, 1.4f };			// 星の半径(遠い星は1pxの点なので使わない)
	static constexpr int STAR_ALPHA[LAYER_COUNT] = { 110, 170, 230 };				// 星の明るさ(0~255)

	// 近い星のにじみ(光は控えめ)
	static const int NEAR_GLOW_ALPHA = 20;			// にじみの濃さ(0~255)
	static constexpr float NEAR_GLOW_SCALE = 3.0f;	// にじみの半径(星の半径の何倍か)

	// 瞬き
	static const int TWINKLE_PERCENT = 25;			// 瞬く星の割合(%)
	static const int TWINKLE_PERIOD = 3000;			// 1回瞬くのにかかる時間(ミリ秒)
	static constexpr float TWINKLE_DEPTH = 0.6f;	// 一番暗いときにどれだけ暗くするか(0~1)

	// 星の色(ほとんど白、たまに薄いシアンと薄いマゼンタ)
	static const int CYAN_PERCENT = 10;				// 薄いシアンの割合(%)
	static const int MAGENTA_PERCENT = 10;			// 薄いマゼンタの割合(%)
	static constexpr NeonColor PALE_CYAN = { 170, 240, 255 };
	static constexpr NeonColor PALE_MAGENTA = { 255, 190, 240 };

	static const int CIRCLE_VERTEX_COUNT = 12;		// 星の円の頂点数

	void Initialize();
	void DrawStar(float x, float y, const Star& star, int alpha);
	static NeonColor PickColor();
	static float Wrap(float value, int size);
};
