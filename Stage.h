#pragma once
#include "common.h"
#include "Camera.h"
#include "StarField.h"

class Stage
{
public:
	GameObject m_field = { {0,0},0,0};
	void InitializeStage();
	void DrawStage(Camera camera);
	int m_width;
	int m_height;

private:
	float m_stageX;
	float m_stageY;

	StarField m_starField;	// 床の上に描く星空
};