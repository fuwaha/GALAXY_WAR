#include <DxLib.h>
#include "Stage.h"
#include "GameSettings.h"
#include "Camera.h"
#include "Neon.h"
#include "DebugDisplay.h"

void Stage::InitializeStage() 
{
	m_stageX = 0;
	m_stageY = 0;
	m_width = 7680;
	m_height = 4320;

	m_field = { {m_stageX,m_stageY},m_width,m_height };
}

void Stage::DrawStage(Camera camera) 
{
	// ステージの画面上の位置
	float left = static_cast<float>(m_field.position.x - camera.m_x);
	float top = static_cast<float>(m_field.position.y - camera.m_y);
	float right = left + m_field.width;
	float bottom = top + m_field.height;

	// 床(暗い紺)
	DrawBox(static_cast<int>(left), static_cast<int>(top), static_cast<int>(right), static_cast<int>(bottom), Neon::ToColor(Neon::FLOOR), TRUE);

	// 星空(カメラの位置に合わせて視差スクロール、瞬きあり)
	m_starField.Draw(static_cast<float>(camera.m_x), static_cast<float>(camera.m_y), true);

	// ステージの外周(光る枠)
	Neon::DrawGlowLine(left, top, right, top, Neon::MAGENTA, 3.0f);
	Neon::DrawGlowLine(right, top, right, bottom, Neon::MAGENTA, 3.0f);
	Neon::DrawGlowLine(right, bottom, left, bottom, Neon::MAGENTA, 3.0f);
	Neon::DrawGlowLine(left, bottom, left, top, Neon::MAGENTA, 3.0f);

	if (DebugDisplay::IsVisible())
		DrawFormatString(20, 100, GetColor(255, 255, 0), L"StagePos X = %.0f Y = %.0f Field = %d", m_field.position.x - camera.m_x, m_field.position.y - camera.m_y, GameSettings::SCREEN_WIDTH + m_field.width);
}