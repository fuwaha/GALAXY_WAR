#pragma once
#include "common.h"

static class PlayerInput 
{
public:
	static enum Input
	{
		Up,
		Down,
		Right,
		Left,

		LeftClick,
		RightClick,
	};
	static bool GetInput(Input input);
	static Vector2 GetMousePos();
	static bool GetMouseClick(Input input);
};