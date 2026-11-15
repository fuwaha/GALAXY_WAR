#include <DxLib.h>
#include <cmath>
#include "StarField.h"
#include "GameSettings.h"

void StarField::Draw(float scrollX, float scrollY, bool isTwinkleOn)
{
	// TitleSceneはDxLib_Initより前に作られるので、最初に描くときに星を並べる
	if (!m_isInitialized)
		Initialize();

	int nowTime = GetNowCount();

	for (const Star& star : m_stars)
	{
		// 近い層ほど大きくずらす。画面からはみ出した分は反対側に回す
		float x = Wrap(star.x - scrollX * LAYER_SCROLL_RATE[star.layer], GameSettings::SCREEN_WIDTH);
		float y = Wrap(star.y - scrollY * LAYER_SCROLL_RATE[star.layer], GameSettings::SCREEN_HEIGHT);

		int alpha = STAR_ALPHA[star.layer];

		// 瞬き(sinでゆっくり暗くなって戻る)
		if (isTwinkleOn && star.isTwinkle)
		{
			float angle = ((nowTime + star.twinkleOffset) % TWINKLE_PERIOD) * 2.0f * DX_PI_F / TWINKLE_PERIOD;
			float darkness = TWINKLE_DEPTH * (0.5f + 0.5f * sinf(angle));
			alpha = static_cast<int>(alpha * (1.0f - darkness));
		}

		DrawStar(x, y, star, alpha);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 星をランダムに並べる
void StarField::Initialize()
{
	m_stars.clear();

	for (int layer = 0; layer < LAYER_COUNT; layer++)
	{
		for (int i = 0; i < STAR_COUNT[layer]; i++)
		{
			Star star;
			star.x = static_cast<float>(GetRand(GameSettings::SCREEN_WIDTH - 1));
			star.y = static_cast<float>(GetRand(GameSettings::SCREEN_HEIGHT - 1));
			star.layer = layer;
			star.color = PickColor();
			star.isTwinkle = GetRand(99) < TWINKLE_PERCENT;
			star.twinkleOffset = GetRand(TWINKLE_PERIOD - 1);
			m_stars.push_back(star);
		}
	}

	m_isInitialized = true;
}

// 星を1つ描く
void StarField::DrawStar(float x, float y, const Star& star, int alpha)
{
	unsigned int color = Neon::ToColor(star.color);

	// 遠い星は1pxの点
	if (star.layer == FAR_LAYER)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawPixel(static_cast<int>(x), static_cast<int>(y), color);
		return;
	}

	float radius = STAR_RADIUS[star.layer];

	// 近い星だけうっすらにじませる(瞬きに合わせてにじみも暗くする)
	if (star.layer == NEAR_LAYER)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, NEAR_GLOW_ALPHA * alpha / STAR_ALPHA[NEAR_LAYER]);
		DrawCircleAA(x, y, radius * NEAR_GLOW_SCALE, CIRCLE_VERTEX_COUNT, color, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawCircleAA(x, y, radius, CIRCLE_VERTEX_COUNT, color, TRUE);
}

// 星の色を決める(ほとんど白、たまに薄いシアンと薄いマゼンタ)
NeonColor StarField::PickColor()
{
	int roll = GetRand(99);
	if (roll < CYAN_PERCENT)
		return PALE_CYAN;
	if (roll < CYAN_PERCENT + MAGENTA_PERCENT)
		return PALE_MAGENTA;
	return Neon::WHITE;
}

// valueを0~sizeの範囲に収める(はみ出した分は反対側から)
float StarField::Wrap(float value, int size)
{
	float result = fmodf(value, static_cast<float>(size));
	if (result < 0.0f)
		result += size;
	return result;
}
