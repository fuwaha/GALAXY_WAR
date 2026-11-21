#pragma once

#include "common.h"
#include "Camera.h"
#include "HitPoint.h"
#include "GameSettings.h"
#include "Gun.h"
#include "Neon.h"

class Enemy
{
public:
	enum class EnemyState
	{
		Alive,
		Dead,
		Damage
	};

	enum class EnemyType
	{
		Common,
		Tank,
		Fast,
		Splash
	};

	EnemyState GetEnemyState() const;
	void SetEnemyState(EnemyState state);

	Vector2 GetPosition() const;
	float GetRadius() const;

	void InitializeEnemy(Vector2 spawnPos,EnemyType enemyType);

	void DrawEnemy(Camera camera);
	void UpdateEnemy(int stageWidth, int stageHeight, Vector2 playerPos);

	bool CheckBulletHit(Vector2 targetPos, float targetRadius);

	void TakeDamage(int amount);

	bool IsActive() const;
	void Activate();

	static const int ATTACK = 10;

private:
	GameObject m_enemyObj;

	//敵の構造体
	struct EnemyParam
	{
		int maxHp;           //体力
		float moveSpeed;     //動く速さ
		float drawRadius;    //大きさ
		int destroyScore;    //倒したときに貰えるスコア
		NeonColor color;     //色
		float shootInterval; //弾を撃つインターバル(秒)
		int bulletCount;     //弾数
	};

	EnemyType m_enemyType = EnemyType::Common;
	EnemyParam m_param = { 0,0,0,0,Neon::BLUE,0,0 };

	static constexpr EnemyParam ENEMY_LIST[] =
	{
		//common
		{
			2,
			2.0f,
			32.0f,
			100,
			Neon::ORANGE,
			1.0f,
			3
		},

		//tank
		{
			5,
			1.0f,
			48.0f,
			300,
			Neon::RED,
			4.0f,
			10
		},

		//fast
		{
			1,
			4.0f,
			16.0f,
			150,
			Neon::BLUE,
			0,
			0
		},

		//splash
		{
			2,
			2.0f,
			32.0f,
			400,
			Neon::ORANGE,
			5.0f,
			60
		}
	};

	bool m_isActive = false;

	//大きさ(あたり判定用、表示に使う大きさはdrawRadius)
	int m_enemyW;
	int m_enemyH;

	//HPのインスタンス
	HitPoint m_hitPoint;

	//弾を発射する銃
	Gun m_gun;
	int m_shootTimer = 0;              //インターバル用のタイマー

	//攻撃を受けた時の点滅(プレイヤーには無敵時間があるけど、敵には無し)
	int m_flashTimer = 0;
	static const int FLASH_TIME = 20;

	EnemyState m_enemyState = EnemyState::Alive;

	float m_angle = 0.0f;	// プレイヤーの方を向いている角度(ラジアン)

	static constexpr float DRAW_RADIUS = 32.0f;		// 体の円の半径
	static constexpr float BODY_THICKNESS = 3.0f;	// 体の線の太さ
	static constexpr float EYE_DISTANCE = 16.0f;	// 中心から目までの距離
	static constexpr float EYE_RADIUS = 4.0f;		// 目の半径
	static constexpr float EYE_THICKNESS = 4.0f;	// 目の線の太さ(半径と同じくらいにすると塗りつぶした点に見える)

};