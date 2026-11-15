#include <DxLib.h>
#include "DebugDisplay.h"

void DebugDisplay::Update()
{
	bool isKeyPressed = CheckHitKey(KEY_INPUT_F1) != 0;

	// 押した瞬間だけ切り替える
	if (isKeyPressed && !m_isKeyHeld)
		m_isVisible = !m_isVisible;

	m_isKeyHeld = isKeyPressed;
}

bool DebugDisplay::IsVisible()
{
	return m_isVisible;
}
