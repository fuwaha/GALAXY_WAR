#pragma once

// F1キーでデバッグ表示(座標などの文字)のON/OFFを切り替えるクラス
class DebugDisplay
{
public:
	static void Update();
	static bool IsVisible();

private:
	static inline bool m_isVisible = false;	// 最初は非表示
	static inline bool m_isKeyHeld = false;	// 押しっぱなしで切り替わり続けないようにする
};
