#include <DxLib.h>
#include "Neon.h"

void Neon::DrawGlowLine(float x1, float y1, float x2, float y2, NeonColor color, float thickness)
{
	// にじみ(外側から順に加算合成)
	SetDrawBlendMode(DX_BLENDMODE_ADD, GLOW_ALPHA);
	for (int i = GLOW_LAYER_COUNT; i >= 1; i--)
	{
		DrawLineAA(x1, y1, x2, y2, ToColor(color), thickness + static_cast<float>(i * GLOW_SPREAD));
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 芯
	DrawLineAA(x1, y1, x2, y2, GetCoreColor(color), thickness);
}

void Neon::DrawGlowCircle(float x, float y, float radius, NeonColor color, float thickness)
{
	// にじみ
	SetDrawBlendMode(DX_BLENDMODE_ADD, GLOW_ALPHA);
	for (int i = GLOW_LAYER_COUNT; i >= 1; i--)
	{
		DrawCircleAA(x, y, radius, CIRCLE_VERTEX_COUNT, ToColor(color), FALSE, thickness + static_cast<float>(i * GLOW_SPREAD));
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 芯
	DrawCircleAA(x, y, radius, CIRCLE_VERTEX_COUNT, GetCoreColor(color), FALSE, thickness);
}

void Neon::DrawGlowTriangle(float x1, float y1, float x2, float y2, float x3, float y3, NeonColor color, float thickness)
{
	// にじみ
	SetDrawBlendMode(DX_BLENDMODE_ADD, GLOW_ALPHA);
	for (int i = GLOW_LAYER_COUNT; i >= 1; i--)
	{
		DrawTriangleAA(x1, y1, x2, y2, x3, y3, ToColor(color), FALSE, thickness + static_cast<float>(i * GLOW_SPREAD));
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 芯
	DrawTriangleAA(x1, y1, x2, y2, x3, y3, GetCoreColor(color), FALSE, thickness);
}

void Neon::DrawGlowString(int x, int y, const TCHAR* text, NeonColor color, int fontHandle)
{
	// にじみ(上下左右に少しずつずらして加算合成)
	SetDrawBlendMode(DX_BLENDMODE_ADD, TEXT_GLOW_ALPHA);
	for (int i = 1; i <= GLOW_LAYER_COUNT; i++)
	{
		int offset = i * TEXT_GLOW_OFFSET;
		DrawStringToHandle(x - offset, y, text, ToColor(color), fontHandle);
		DrawStringToHandle(x + offset, y, text, ToColor(color), fontHandle);
		DrawStringToHandle(x, y - offset, text, ToColor(color), fontHandle);
		DrawStringToHandle(x, y + offset, text, ToColor(color), fontHandle);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 芯
	DrawStringToHandle(x, y, text, GetCoreColor(color), fontHandle);
}

unsigned int Neon::ToColor(NeonColor color)
{
	return GetColor(color.r, color.g, color.b);
}

unsigned int Neon::GetCoreColor(NeonColor color)
{
	// 元の色を白に6割近づけて、光の中心っぽくする
	int coreR = color.r + (255 - color.r) * 6 / 10;
	int coreG = color.g + (255 - color.g) * 6 / 10;
	int coreB = color.b + (255 - color.b) * 6 / 10;
	return GetColor(coreR, coreG, coreB);
}
