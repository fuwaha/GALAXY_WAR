#include <algorithm>
#include "Camera.h"
#include "GameSettings.h"

void Camera::InitializeCamera()
{
	m_x = 3080;
	m_y = 1320;
};

void Camera::FollowCamera(Vector2 playerPos, int stageWidth, int stageHeight)
{
    m_x = std::clamp(
        static_cast<int>(playerPos.x) - GameSettings::SCREEN_WIDTH / 2,
        0,
        stageWidth - GameSettings::SCREEN_WIDTH
    );

    m_y = std::clamp(
        static_cast<int>(playerPos.y) - GameSettings::SCREEN_HEIGHT / 2,
        0,
        stageHeight - GameSettings::SCREEN_HEIGHT
    );
};