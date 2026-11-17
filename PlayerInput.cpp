#include <DxLib.h>
#include "PlayerInput.h"
#include "common.h"


//||を重ねることで他の入力でも上下左右のInputに変換できる
//多分もっといい書き方があると思うけど、とりあえずこれ

bool isClicked = false;

bool PlayerInput::GetInput(Input input) 
{
	if (input == Input::Up)
		return CheckHitKey(KEY_INPUT_W) ||
		CheckHitKey(KEY_INPUT_UP);

	if (input == Input::Down)
		return CheckHitKey(KEY_INPUT_S) ||
		CheckHitKey(KEY_INPUT_DOWN);

	if (input == Input::Right)
		return CheckHitKey(KEY_INPUT_D) ||
		CheckHitKey(KEY_INPUT_RIGHT);

	if (input == Input::Left)
		return CheckHitKey(KEY_INPUT_A) ||
		CheckHitKey(KEY_INPUT_LEFT);
}

Vector2 PlayerInput::GetMousePos() 
{
	int x;
	int y;
	GetMousePoint(&x, &y);

	return Vector2(static_cast<float>(x), static_cast<float>(y));
}

bool PlayerInput::GetMouseClick(Input input)
{


	if (input == Input::LeftClick &&
		(GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		if (isClicked) return false;

		isClicked = true;
		return true;
	}

	if (input == Input::RightClick &&
		(GetMouseInput() & MOUSE_INPUT_RIGHT))
	{
		if (isClicked) return false;

		isClicked = true;
		return true;
	}

	isClicked = false;

	return false;
}