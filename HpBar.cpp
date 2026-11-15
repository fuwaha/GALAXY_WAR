#include <DxLib.h>
#include <algorithm>
#include "HpBar.h"

void HpBar::Draw(int hp, int maxHp)
{
	// 最大HPが0以下だと割り算できないので何もしない
	if (maxHp <= 0)
		return;

	// HPの割合から中身の幅を出す(0~BAR_WIDTHに収める)
	int clampedHp = std::clamp(hp, 0, maxHp);
	int fillWidth = BAR_WIDTH * clampedHp / maxHp;

	int left = BAR_X;
	int top = BAR_Y;
	int right = BAR_X + BAR_WIDTH;
	int bottom = BAR_Y + BAR_HEIGHT;

	// 減った部分(薄く塗る)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, EMPTY_ALPHA);
	DrawBox(left + fillWidth, top, right, bottom, Neon::ToColor(BAR_COLOR), TRUE);

	// 残っている部分
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FILL_ALPHA);
	DrawBox(left, top, left + fillWidth, bottom, Neon::ToColor(BAR_COLOR), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 光る枠
	float l = static_cast<float>(left);
	float t = static_cast<float>(top);
	float r = static_cast<float>(right);
	float b = static_cast<float>(bottom);
	Neon::DrawGlowLine(l, t, r, t, BAR_COLOR, FRAME_THICKNESS);
	Neon::DrawGlowLine(r, t, r, b, BAR_COLOR, FRAME_THICKNESS);
	Neon::DrawGlowLine(r, b, l, b, BAR_COLOR, FRAME_THICKNESS);
	Neon::DrawGlowLine(l, b, l, t, BAR_COLOR, FRAME_THICKNESS);
}
