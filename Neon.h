#pragma once
#include <DxLib.h>

// ネオンの色(R,G,B)
struct NeonColor
{
	int r;
	int g;
	int b;
};

// ネオン風(光って見える)図形・文字の描画をまとめたクラス
// 外側ほど太く薄く加算合成で重ねて「にじみ」を作り、最後に白っぽい芯を描く
class Neon
{
public:
	// ゲーム全体で使う色
	static constexpr NeonColor CYAN = { 0, 255, 255 };			
	static constexpr NeonColor MAGENTA = { 255, 60, 220 };		
	static constexpr NeonColor RED = { 255,0,0 };               
	static constexpr NeonColor BLUE = { 60, 140, 255 };
	static constexpr NeonColor ORANGE = { 255, 140, 0 };        
	static constexpr NeonColor YELLOW = { 255,220,0 };
	static constexpr NeonColor WHITE = { 255,255,255 };
	static constexpr NeonColor FLOOR = { 8, 10, 24 };			// 床・背景
	static constexpr NeonColor TEXT_DIM = { 90, 140, 170 };		// 控えめな文字

	static void DrawGlowLine(float x1, float y1, float x2, float y2, NeonColor color, float thickness);
	static void DrawGlowCircle(float x, float y, float radius, NeonColor color, float thickness);
	static void DrawGlowTriangle(float x1, float y1, float x2, float y2, float x3, float y3, NeonColor color, float thickness);
	static void DrawGlowString(int x, int y, const TCHAR* text, NeonColor color, int fontHandle);

	static unsigned int ToColor(NeonColor color);

private:
	static const int GLOW_LAYER_COUNT = 2;		// にじみを重ねる枚数
	static const int GLOW_ALPHA = 25;			// にじみ1枚の濃さ(0~255)
	static const int GLOW_SPREAD = 3;			// にじみ1枚ごとに太くする量
	static const int TEXT_GLOW_ALPHA = 15;		// 文字のにじみ1枚の濃さ(読みやすさ優先で図形より弱め)
	static const int TEXT_GLOW_OFFSET = 1;		// 文字のにじみ1枚ごとにずらす量
	static const int CIRCLE_VERTEX_COUNT = 32;	// 円の頂点数

	static unsigned int GetCoreColor(NeonColor color);
};
