#pragma once
#include "common.h"

class Camera
{
public:
	int m_x;
	int m_y;
	void InitializeCamera();
	void FollowCamera(Vector2 playerPos, int stageWidth, int stageHeight);
};