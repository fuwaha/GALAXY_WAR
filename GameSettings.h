#pragma once

static class GameSettings
{
public:
	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;

	static const int FPS = 60;                      //ゲーム内のタイマーはこれを基準にしてる
	static const int FRAME_TIME = 1000000 / FPS;	// 1フレームの時間(マイクロ秒)=16666
};