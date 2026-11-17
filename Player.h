#pragma once
#include "common.h"
#include "Gun.h"
#include "Camera.h"
#include "HitPoint.h"
#include "GameSettings.h"

class Player
{
public:
	GameObject m_playerObj;

	static const int ATTACK = 1;

	enum class PlayerState
	{
		Alive,
		Dead,
		Damage,
	};

	const HitPoint& GetHitPoint() const { return m_hitPoint; }

	PlayerState GetPlayerState() const;
	void SetPlayerState(PlayerState state);

	Vector2 GetPosition() const;
	float GetRadius() const;

	void InitializePlayer();

	void DrawPlayer(Camera camera);
	void UpdatePlayer(int stageWidth, int stageHeight, Camera camera);

	bool CheckBulletHit(Vector2 targetPos, float targetRadius);

	void TakeDamage(int amount);

	int GetMoveSpeed();

private:
	float m_playerPosX;
	float m_playerPosY;
	int m_playerW;
	int m_playerH;

	static const int MOVE_SPEED = 4;

	void UpdateAim(Camera camera);
	void PlayerControl(int stageWidth, int stageHeight);

	Vector2 m_aimDirection = { 0,0 };
	float m_angle = 0;

	HitPoint m_hitPoint;
	static const int MAX_HP = 100;//体力

	Gun m_gun;
	static const int BULLET_COUNT = 5; //弾数

	//被ダメージ後の無敵時間とそのタイマー
	static const int INVINCIBLE_SECONDS = 1;//無敵時間(秒)

	int m_invincibleTimer = 0;
	static const int INVINCIBLE_TIME = GameSettings::FPS * INVINCIBLE_SECONDS;

	PlayerState m_playerState = PlayerState::Alive;

	static constexpr float DRAW_SIZE = 32.0f;	// 描画する三角形の大きさ(中心から先端まで)
	static constexpr float BACK_ANGLE = 2.5f;	// 先端から後ろの角までの角度(ラジアン)

	const TCHAR* GetStateName() const;
};